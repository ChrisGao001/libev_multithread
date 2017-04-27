//
// Created by sean on 4/26/17.
//

#include "smart_thing.h"

smart_lock::smart_lock(pthread_mutex_t mutex){
    _mutex = mutex;
    pthread_mutex_lock(&_mutex);
}
smart_lock::~smart_lock(){
    pthread_mutex_unlock(&_mutex);
}