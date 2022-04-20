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
#include "message.cpp"
using namespace std;

#ifndef PROYECTO1DATOS2_CLIENT_H
#define PROYECTO1DATOS2_CLIENT_H

class client {
public:
    client();
    bool START = true;
    string imageReceived;
    int sockfd; 
    struct sockaddr_in servaddr;
    struct message* sendRequest(struct message request);
    int instruction = 0;
    int size = 0;

private:
    struct message buf_tx;      
    struct message buf_rx;
};

#endif //PROYECTO1DATOS2_CLIENT_H