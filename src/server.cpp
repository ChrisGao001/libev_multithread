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
    _work_num = 0;
    _thisPtr = this;
}

server::~server() {
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond);
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
        ev_async_init(&para->async_watcher, nullptr);
        ev_async_start(para->loop, &para->async_watcher);

        pthread_t thread;
        pthread_attr_t attr;
        pthread_create(&thread, &attr, server::create_work_thread, (void*)para);
    }
}

void* server::create_work_thread(void *n){
    _thisPtr->create_thread(n);
    return nullptr;
}

void server::accept_server_cb(struct ev_loop *loop, struct ev_io *w, int events){
    _thisPtr->accept_cb(loop, w, events);
}

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
void server::accept_cb(struct ev_loop *loop, struct ev_io *w, int events){
    int newfd;
    struct sockaddr addr;
    socklen_t len = sizeof(struct sockaddr);
    while((newfd =accept(w->fd, (struct sockaddr*)&addr, &len)) < 0){
        if(errno == EAGAIN || errno == EWOULDBLOCK){
            continue;
        } else {
            break;
        }
    }
    if(newfd > 0){

    }
}

void server::create_thread(void *n){
    work_thread_para* para = (work_thread_para*)n;
    para->tid = pthread_self();
    ev_loop(para->loop, 0);
    smart_lock lock(_mutex);
    ++_work_num;
}
