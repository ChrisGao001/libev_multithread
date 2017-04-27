//
// Created by sean on 4/26/17.
//

#ifndef LIBEV_MULTITHREAD_DEFINE_H
#define LIBEV_MULTITHREAD_DEFINE_H

#include <pthread.h>

#define SAFE_DEL(ptr) \
if(ptr != nullptr){   \
delete ptr;           \
}
#endif //LIBEV_MULTITHREAD_DEFINE_H
