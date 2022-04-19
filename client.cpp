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

#define SERVER_ADDRESS  "192.168.0.8"
#define PORT            8080 

client::client(){
    
}

struct message*  client::sendRequest(struct message request){ 

    /* Socket creation */
    buf_tx = request;
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        printf("CLIENT: socket creation failed...\n"); 
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
        printf("connection with the server failed...\n");  
    } 
    
    printf("connected to the server..\n");

    write(sockfd, (struct message *)&buf_tx, sizeof(buf_tx));
    printf("CLIENT: ID SENT, WAITING FOR SIZE OF THE NEXT PACKAGE \n");    

    read(sockfd, (struct message *)&buf_rx, sizeof(buf_rx));
    printf("CLIENT: SIZE AND INSTRUCTION OF PACKAGE RECEIVED \n");

    imageReceived.clear();
    size = buf_rx.ID;
    instruction = buf_rx.instruction;
    
    printf("CLIENT: RECEIVED SIZE %d \n", size);
    printf("CLIENT: RECEIVED INSTRUCTION: %d \n", instruction);
    printf("CLIENT: WAITING FOR PACKAGE WITH THE IMAGE \n");

    char* temp = (char*)malloc(sizeof(char) * size);
    read(sockfd, temp, size);
    for(int i = 0; i < size; i++){
        imageReceived.push_back(*(temp+i));
    }

    struct message* answer;
    answer = ((struct message *)&buf_rx);
    printf("CLIENT: RETURNED THE STRUCT WITH THE DATA \n");
       
    /* close the socket */
    close(sockfd); 
    
    return answer;
} 