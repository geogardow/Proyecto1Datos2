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
#include "card.h"
using namespace std;

#ifndef PROYECTO1DATOS2_CLIENT_H
#define PROYECTO1DATOS2_CLIENT_H

class client {
public:
    client();
    int sockfd; 
    struct sockaddr_in servaddr;
    struct message {
        int ID;
        string loadedPic;
    };
    struct message sendRequest(struct message position);
    int instruction = 0;

private:
    struct message buf_tx;      
    struct message buf_rx;
};

#endif //PROYECTO1DATOS2_CLIENT_H