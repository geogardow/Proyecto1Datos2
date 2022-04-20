#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include "client.h"
#include "card.h"
#include <chrono>
#include <thread>

#define SERVER_ADDRESS  "172.18.227.171"
#define PORT            8080 

client::client(){
    
}

/**
 * @brief In charge of requesting information from the server in order to update the interface
 * 
 * @param request 
 * @return struct message* 
 */
struct message*  client::sendRequest(struct message request){ 

    /* Socket creation */
    buf_tx = request;
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        cout<<"[CLIENT-error]: socket creation failed...\n"<<endl;
    } 
    
    /* memory space cleaning */
    memset(&servaddr, 0, sizeof(servaddr));

    /* assign IP, PORT */
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr( SERVER_ADDRESS ); 
    servaddr.sin_port = htons(PORT); 
  
    /* try to connect the client socket to server socket */
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) 
    { 
        cout<<"[CLIENT-error]: connection with the server failed...\n"<<endl;
    } 

    if (START)
    {   
        read(sockfd, (struct message *)&buf_rx, sizeof(buf_rx)); //CLIENT: RECEIVES THE FIRST PLAYER
        this->START = false;
        struct message* answer;
        answer = ((struct message *)&buf_rx); //CLIENT: RETURNED THE STRUCT WITH THE DATA
        close(sockfd); 
        return answer;
    }

    write(sockfd, (struct message *)&buf_tx, sizeof(buf_tx)); //CLIENT: ID SENT, WAITING FOR SIZE OF THE NEXT PACKAGE    

    read(sockfd, (struct message *)&buf_rx, sizeof(buf_rx)); //CLIENT: SIZE AND INSTRUCTION OF PACKAGE RECEIVED

    imageReceived.clear();
    size = buf_rx.ID;
    instruction = buf_rx.instruction;
    
    char* temp = (char*)malloc(sizeof(char) * size);
    read(sockfd, temp, size); //CLIENT: WAITING FOR PACKAGE WITH THE IMAGE
    for(int i = 0; i < size; i++){
        imageReceived.push_back(*(temp+i));
    }

    struct message* answer;
    answer = ((struct message *)&buf_rx); //CLIENT: RETURNED THE STRUCT WITH THE DATA
       
    /* close the socket */
    close(sockfd); 
    
    return answer;
} 