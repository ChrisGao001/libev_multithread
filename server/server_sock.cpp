//
// Created by sean on 4/26/17.
//

#include "server_sock.h"
server_sock::server_sock(){

}
server_sock::~server_sock(){

}

bool server_sock::init(int* lsn){
    *lsn = socket(AF_INET, SOCK_STREAM, 0);
    if(*lsn == -1){
        return false;
    }

    int addrreuse = 1;
    setsockopt(*lsn, SOL_SOCKET, SO_REUSEADDR, &addrreuse, sizeof(addrreuse));

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(16960);

    int rst = bind(*lsn, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    if(rst == -1){
        return  false;
    }

    rst = listen(*lsn, 102400);
    if(rst == -1){
        return  false;
    }
    return true;
}