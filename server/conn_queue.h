//
// Created by sean on 4/25/17.
//

#ifndef LIBEV_MULTITHREAD_CONN_QUEUE_H
#define LIBEV_MULTITHREAD_CONN_QUEUE_H

#include <sys/param.h>
#include "smart_thing.h"

struct conn_node{
    int fd;
    char addr[16];
    int port;
    conn_node* next;
};

class conn_queue{
public:
    conn_queue();
    ~conn_queue();
    void push(conn_node* node);
    conn_node* pop();
private:
    conn_node* _head;
    conn_node* _tail;
    pthread_mutex_t _mutex;
};

#endif //LIBEV_MULTITHREAD_CONN_QUEUE_H
