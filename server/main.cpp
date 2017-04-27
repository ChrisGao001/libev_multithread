#include "server.h"

int main(){
    server s;
    s.create_work(5);
    s.register_sock();
    return 0;
}
