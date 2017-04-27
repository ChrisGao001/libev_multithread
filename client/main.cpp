//
// Created by sean on 4/27/17.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

bool init(int* fd){
    *fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(16960);
    int ret = connect(*fd, (struct sockaddr*)&addr, sizeof(struct sockaddr));
    if(ret == -1){
        return false;
    }
    return true;
}

int main(int argc, char** args){
    int fd = 0;
    int fdo = 0;
    while(1){
        if(!init(&fd)){
            break;
        }
        fdo = fd;
        usleep(100);
    }
    printf("%d", fdo);
}