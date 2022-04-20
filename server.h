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
#include "cardSelector.cpp"
using namespace std;

#ifndef PROYECTO1DATOS2_SERVER_H
#define PROYECTO1DATOS2_SERVER_H

class server {
private:
    int sockfd, connfd; 
    unsigned int len;
    struct sockaddr_in servaddr, client; 
    int  len_rx, len_tx = 0;
    cardSelector matrix = cardSelector();
    image serverImageMan = image();
    struct message buff_tx;
    struct message buff_rx;
    card actualCard = card(0,0,0,0);
    int idCard1 = 0;
    int idCard2 = 0;
    int idPic1 = 0;
    int idPic2 = 0;
    int actualCardID = 0;
    int actualPicID = 0;
    int turn;
    int pointsP1 = 0;
    int pointsP2 = 0;
    bool HIT1 = false;
    bool HIT2 = false;
    bool WINNER = false;
    bool WINBREAK = false;


public:
    server();
    bool START = true;
    int start();
    void addPoints();
    void subsPoints();
    void switchPlayers();
    void doublePoints();
    void switchPoints();
};

#endif //PROYECTO1DATOS2_SERVER_H