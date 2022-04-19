#ifndef PROYECTO1DATOS2_CARD_H
#define PROYECTO1DATOS2_CARD_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
using namespace std;



class card{
    public:
    card(int i , int j , int idPic , int status);
    string img;
    int i, j, idPic, status;
};

#endif //PROYECTO1DATOS2_CARD_H