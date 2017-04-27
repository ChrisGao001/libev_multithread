//
// Created by sean on 4/25/17.
//

#include <sys/param.h>
#include "server.h"


server* server::_thisPtr;
server::server() {
    pthread_mutex_init(&_mutex, nullptr);
    pthread_cond_init(&_cond, nullptr);
    _sock = new server_sock();
    _disp_para = new dispatcher_thead_para();
    _disp_para->loop = ev_default_loop(0);
    _disp_para->tid = pthread_self();
    _work_para_vec.clear();
    _work_num = 0;
    _robin_num = 0;
    _thisPtr = this;
}

server::~server() {
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond);
    _work_para_vec.clear();
    SAFE_DEL(_sock)
    SAFE_DEL(_disp_para)
}

void server::register_sock(){
    int fd = -1;
    _sock->init(&fd);
    ev_io_init(&_disp_para->io_watcher, server::accept_server_cb, fd, EV_READ);
    ev_io_start(_disp_para->loop, &_disp_para->io_watcher);
    ev_loop(_disp_para->loop, 0);
}

void server::create_work(int num) {
    while(num--){
        work_thread_para* para = new work_thread_para;
        para->loop = ev_loop_new(0);
        para->cq = new conn_queue;
        ev_async_init(&para->async_watcher, async_server_cb);
        ev_async_start(para->loop, &para->async_watcher);

        para->async_watcher.data = para;
        pthread_t thread;
        pthread_attr_t attr;
        int ret = pthread_create(&thread, nullptr, create_work_thread, (void*)para);
        if(ret != 0){
            exit(0);
        }
    }
}

void* server::create_work_thread(void *n){
    _thisPtr->create_thread(n);
}

void server::accept_server_cb(struct ev_loop *loop, struct ev_io *w, int events){
    _thisPtr->accept_cb(loop, w, events);
}

void server::async_server_cb(struct ev_loop *loop, struct ev_async *w, int events){
    _thisPtr->async_cb(loop, w, events);
}

void server::accept_cb(struct ev_loop *loop, struct ev_io *w, int events){
    int newfd;
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    while((newfd =accept(w->fd, (struct sockaddr*)&addr, &len)) < 0){
        if(errno == EAGAIN || errno == EWOULDBLOCK){
            continue;
        } else {
            break;
        }
    }
    if(newfd > 0){
        dispatch_conn(newfd, addr);
    }
}

void server::async_cb(struct ev_loop *loop, struct ev_async *w, int events){
    conn_node* node = ((work_thread_para*)(w->data))->cq->pop();
    if(node == nullptr){
        return;
    }
    printf("async to process fd: %d\n", node->fd);
    //ev_io io_watcher;
    //ev_io_init(&io_watcher, nullptr, node->fd, EV_READ);
    //ev_io_start(((work_thread_para*)(w->data))->loop, &io_watcher);
    delete node;
    node = nullptr;
}

void server::dispatch_conn(int fd, struct sockaddr_in addrin){
    conn_node* node = new conn_node();
    node->fd = fd;
    strcpy(node->addr, (char*)inet_ntoa(addrin.sin_addr));
    node->port = addrin.sin_port;
    int size = _work_para_vec.size();

    int robin = _robin_num%_work_num;
    _work_para_vec[robin]->cq->push(node);
    ev_async_send(_work_para_vec[robin]->loop, &_work_para_vec[robin]->async_watcher);
    _robin_num++;
}

void server::create_thread(void *n){
    work_thread_para* para = (work_thread_para*)n;
    para->tid = pthread_self();
    {
        smart_lock lock(_mutex);
        int size = _work_para_vec.size();
        _work_para_vec.push_back(para);
        ++_work_num;
    }
    ev_loop(para->loop, 0);
    return;
}
