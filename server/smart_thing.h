//
// Created by sean on 4/26/17.
//

#ifndef LIBEV_MULTITHREAD_SMART_THING_H
#define LIBEV_MULTITHREAD_SMART_THING_H
#include "define.h"

class smart_lock {
public:
    smart_lock(pthread_mutex_t mutex);
    ~smart_lock();
private:
    pthread_mutex_t _mutex;
};


#endif //LIBEV_MULTITHREAD_SMART_THING_H
