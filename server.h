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
#include "image.cpp"
using namespace std;

#ifndef PROYECTO1DATOS2_SERVER_H
#define PROYECTO1DATOS2_SERVER_H

class server {
private:
    int sockfd, connfd; 
    unsigned int len;
    struct sockaddr_in servaddr, client; 
    int  len_rx, len_tx = 0;
    image img = image();
    char picture[30000];
    struct message buff_tx;
    struct message buff_rx;
    int idCard1=0;
    int idCard2=0;
    int idPic1=0;
    int idPic2=0;

public:
    server();
    int start();
};

#endif //PROYECTO1DATOS2_SERVER_H