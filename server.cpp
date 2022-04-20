#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string>
#include "server.h"
#include <iostream>

#define SERV_PORT 8080                 /* port */
#define SERV_HOST_ADDR "172.18.227.171"   /* IP, only IPV4 support  */
#define BACKLOG 5                      /* Max. client pending connections  */

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    server s = server();
    s.start();
    return 0;
}
/**
 * @brief Construct a new server::server object
 * 
 */
server::server()
{
}

/**
 * @brief 
 * 
 * @return int 
 */
int server::start()
{

    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        cout<<stderr<<" [SERVER-error]: socket creation failed "<<errno<<strerror(errno)<<endl;
        return -1;
    }
    else
    {
        //[SERVER]: Socket successfully created
    }

    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));

    /* assign IP, SERV_PORT, IPV4 */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    servaddr.sin_port = htons(SERV_PORT);

    /* Bind socket */
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
    {
        cout<<stderr<<" [SERVER-error]: socket bind failed "<<errno<<strerror(errno)<<endl;
        return -1;
    }
    else
    {
        //[SERVER]: Socket successfully binded
    }

    while (1){

        /* Listen */
        if ((listen(sockfd, BACKLOG)) != 0)
        {
            cout<<stderr<<" [SERVER-error]: socket listen failed "<<errno<<strerror(errno)<<endl;
            return -1;
        }
        else
        {
            //[SERVER]: Listening on SERV_PORT 8080
        }

        len = sizeof(client);

        /* Accept the data from incoming sockets in a iterative way */
        connfd = accept(sockfd, (struct sockaddr *)&client, &len);
        if (connfd < 0)
        {
            cout<<stderr<<" [SERVER-error]: connection not accepted "<<errno<<strerror(errno)<<endl;
            return -1;
        }
        else
        {
            while (1) /* read data from a client socket till it is closed */
            {
                if (START)
                {
                    turn = rand()%2+1;
                    buff_tx.turn = turn;
                    write(connfd, (struct message *)&buff_tx, sizeof(buff_tx)); //CLIENT: RECEIVES THE FIRST PLAYER
                    this->START = false;
                    close(connfd);
                    break; 
                }
                /* read client message, copy it into buffer */
                len_rx = read(connfd, (char *)&buff_rx, sizeof(buff_rx)); //[SERVER]: PACKAGE RECEIVED FROM CLIENT, CONTAINS ID AND INSTRUCTION

                if (len_rx == -1)
                {
                    fprintf(stderr, "[SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror(errno));
                }
                else if (len_rx == 0) /* if length is 0 client socket closed, then exit */
                {
                    printf("[SERVER]: client socket closed \n\n");
                    close(connfd);
                    break;
                }
                else
                {
                    actualCardID = buff_rx.ID;
                    actualCard = matrix.getCard(actualCardID/10, actualCardID%10);
                    actualPicID = actualCard.idPic;                  
                                        
                    buff_tx.ID = actualCard.img.size();
                    
                    //[SERVER]: PROCEEDING TO ANALIZE HOW MANY CARDS HAVE BEEN CLICKED AND IF THEY MATCHED
                    if (idCard1 == 0) //[SERVER]: FIRST CARD CLICKED
                    {
                        HIT1 = matrix.HIT;
                        idCard1 = actualCardID;
                        buff_tx.picID = idPic1;
                        buff_tx.pointsP1 = pointsP1;
                        buff_tx.pointsP2 = pointsP2;
                        buff_tx.turn = turn;
                        idPic1 = actualPicID; //aqui se pone el id de la imagen mediante el algoritmo de busqueda
                        buff_tx.instruction = 0; //significa que todavía no hay acción
                    }
                    else if (idCard1 != 0) //[SERVER]: SECOND CARD CLICKED
                    {
                        HIT2 = matrix.HIT;
                        idCard2 = actualCardID;
                        idPic2 = actualPicID;
                        if (idPic1 == idPic2) //[SERVER]: CARDS MATCHED
                        {
                            if (HIT1 && HIT2)
                            {
                                this->addPoints();
                                buff_tx.HIT = 1;
                            }
                            else
                            {
                                buff_tx.HIT = 0;
                            }

                            if (idPic1 == 1)
                            {
                                this->addPoints();
                            }
                            else if (idPic1 == 2)
                            {
                                this->addPoints();
                                this->doublePoints();
                                this->switchPlayers();
                            }
                            else if (idPic1 == 3)
                            {
                                if (turn == 1 && pointsP2 > pointsP1)
                                {
                                    this->switchPoints();
                                    this->addPoints();
                                    this->switchPlayers();
                                    buff_tx.switched = 1;
                                } 
                                else if (turn == 2 && pointsP1 > pointsP2)
                                {
                                    this->switchPoints();
                                    this->addPoints();
                                    this->switchPlayers();
                                    buff_tx.switched = 1;
                                }
                                else
                                {
                                    this->addPoints();
                                    this->switchPlayers();
                                    buff_tx.switched = 0;
                                }
                            }
                            else if (idPic1 == 4)
                            {
                                this->addPoints();
                                this->switchPlayers();
                                this->subsPoints();
                            }
                            else
                            {
                                this->addPoints();
                                this->switchPlayers();
                            }
                            buff_tx.instruction = -1;
                            matrix.deleteCard(idCard1/10, idCard1%10);
                            matrix.deleteCard(idCard2/10, idCard2%10);
                            matrix.shuffle();
                        }
                        else  //[SERVER]: CARDS DID NOT MATCH
                        {
                            this->switchPlayers();
                            buff_tx.instruction = -2;
                        }
                        
                        buff_tx.winner = 0;
                        if (WINNER)
                        {
                            if (pointsP1 > pointsP2)
                            {
                                buff_tx.winner = 1;
                            }
                            else if (pointsP2 > pointsP1)
                            {
                                buff_tx.winner = 2;
                            }
                            else
                            {
                                buff_tx.winner = 3;
                            }
                        }
                        if (matrix.vectorCard.size() == 0)
                        {
                            WINNER = true;
                        }

                        buff_tx.picID = idPic1;
                        buff_tx.pointsP1 = pointsP1;
                        buff_tx.pointsP2 = pointsP2;
                        buff_tx.turn = turn;
                        idCard1 = 0;
                        idPic1 = 0;
                        idCard2 = 0;
                        idPic2 = 0;
                    }
                    
                    
                    write(connfd, (struct message *)&buff_tx, sizeof(buff_tx)); //[SERVER]: PROCEEDING TO SEND SIZE OF THE NEXT PACKAGE AND INSTRUCTION

                    write(connfd, actualCard.img.data(), actualCard.img.size()); //[SERVER]: PROCEEDING TO SEND THE PACKAGE WITH THE IMAGE

                    close(connfd);
                    break;
                }  
            }
        }
    }
}

/**
 * @brief Adds points to player
 * 
 */
void server::addPoints()
{
    if (this->turn == 1)
    {
        this->pointsP1++;
    }
    else
    {
        this->pointsP2++;
    }
}
/**
 * @brief Doubles the points for the player
 * 
 */
void server::doublePoints()
{
    if (this->turn == 1)
    {
        this->pointsP1 = this->pointsP1*2;
    }
    else
    {
        this->pointsP2 = this->pointsP2*2;
    }
}
/**
 * @brief Substracts points from the player
 * 
 */
void server::subsPoints()
{
    if (this->turn == 1)
    {
        this->pointsP1--;
    }
    else
    {
        this->pointsP2--;
    }
}
/**
 * @brief Switches points from one player to another
 * 
 */
void server::switchPoints()
{
    int temp = this->pointsP1;
    this->pointsP1 = this->pointsP2;
    this->pointsP2 = temp;
}
/**
 * @brief Changes the turn of the player
 * 
 */
void server::switchPlayers()
{
    if (this->turn == 1)
    {
        this->turn = 2;
    }
    else
    {
        this->turn = 1;
    }
}