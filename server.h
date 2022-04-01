#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <string>

#ifndef PROYECTO1DATOS2_SERVER_H
#define PROYECTO1DATOS2_SERVER_H

class server {
private:
    int sockfd, connfd; 
    unsigned int len;
    struct sockaddr_in servaddr, client; 
    int  len_rx, len_tx = 0;
    char buff_tx;
    char buff_rx;

public:
    server();
    int start();
};

#endif //PROYECTO1DATOS2_SERVER_H