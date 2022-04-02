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

#ifndef PROYECTO1DATOS2_CLIENT_H
#define PROYECTO1DATOS2_CLIENT_H

class client {
private:
    struct message {
        int ID;
    };
    struct message buf_tx;      
    struct message buf_rx;
    int sockfd; 
    struct sockaddr_in servaddr;

public:
    client();
    struct message request;
    int sendRequest(struct message position);
};

#endif //PROYECTO1DATOS2_CLIENT_H