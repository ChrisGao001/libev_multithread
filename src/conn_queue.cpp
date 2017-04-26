//
// Created by sean on 4/25/17.
//

#include "conn_queue.h"
conn_queue::conn_queue(){
    pthread_mutex_init(&_mutex, nullptr);
    _head = nullptr;
    _tail = nullptr;
}

conn_queue::~conn_queue(){}

void conn_queue::push(conn_node* node){
    smart_lock lock(_mutex);
    if(_tail == nullptr){
        _head = node;
    } else{
        _tail->next = node;
    }
    _tail = node;
}

conn_node* conn_queue::pop(){
    smart_lock lock(_mutex);
    if(_head == nullptr){
        return  nullptr;
    }
    conn_node* node = _head;
    _head = node->next;
    if(_head == nullptr){
        _tail = nullptr;
    }
    return node;
}