//
// Created by sean on 4/25/17.
//

#ifndef LIBEV_MULTITHREAD_SERVER_H
#define LIBEV_MULTITHREAD_SERVER_H


#include <sys/param.h>
#include <arpa/inet.h>
#include <vector>
#include <ev.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include "define.h"
#include "conn_queue.h"
#include "server_sock.h"
using std::vector;


struct work_thread_para{
    pthread_t tid;
    struct ev_loop* loop;
    struct ev_async async_watcher;
    conn_queue* cq;
};
struct dispatcher_thead_para{
    pthread_t tid;
    struct ev_loop* loop;
    struct ev_io io_watcher;
};


class server {
public:
    server();
    ~server();
    void register_sock();
    void create_work(int num);
    static void* create_work_thread(void *n);
    static void accept_server_cb(struct ev_loop *loop, struct ev_io *w, int events);
    static void async_server_cb(struct ev_loop *loop, struct ev_async *w, int events);
    void create_thread(void *n);
    void accept_cb(struct ev_loop *loop, struct ev_io *w, int events);
    void async_cb(struct ev_loop *loop, struct ev_async *w, int events);
    void dispatch_conn(int fd, struct sockaddr_in addrin);
private:
    static server* _thisPtr;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;
    server_sock* _sock;
    struct dispatcher_thead_para * _disp_para;
    vector<work_thread_para*> _work_para_vec;
    int _work_num;
    int _robin_num;
};


#endif //LIBEV_MULTITHREAD_SERVER_H
