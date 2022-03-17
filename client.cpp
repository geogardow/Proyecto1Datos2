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

#define SERVER_ADDRESS  "192.168.0.35"
#define PORT            8080 

client::client(){
    
}

int client::sendRequest(std::string position){ 

    /* Socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        printf("CLIENT: socket creation failed...\n"); 
        return -1;  
    } 
    else
    {
        printf("CLIENT: Socket successfully created..\n"); 
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
        return -1;
    } 
    
    printf("connected to the server..\n"); 
  
    /* send test sequences*/
    write(sockfd, (char *)&buf_tx, sizeof(buf_tx));     
    read(sockfd, (char *)&buf_rx, sizeof(buf_rx));
    printf("CLIENT:Received: %s \n", (char *)&buf_rx);
       
    /* close the socket */
    close(sockfd); 
} 