//
// Created by sean on 4/26/17.
//

#ifndef LIBEV_MULTITHREAD_SOCK_H
#define LIBEV_MULTITHREAD_SOCK_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

class server_sock {
public:
    server_sock();
    ~server_sock();
    bool init(int* lsn);
private:
};


#endif //LIBEV_MULTITHREAD_SOCK_H
