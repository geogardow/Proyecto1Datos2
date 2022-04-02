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

#define SERVER_ADDRESS  "192.168.3.105"
#define PORT            8080 

client::client(){
    
}

int client::sendRequest(struct message position){ 

    /* Socket creation */
    buf_tx=position;
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        printf("CLIENT: socket creation failed...\n"); 
        return -1;  
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
    write(sockfd, (struct message *)&buf_tx, sizeof(buf_tx));     
    read(sockfd, (struct message *)&buf_rx, sizeof(buf_rx));
    instruction = ((struct message *)&buf_rx)->ID;
    printf("CLIENT:Received: %d \n", instruction);

    if (instruction == 0)
    {
        printf("CLIENT: Falta 1 carta de presionar \n");
        //objeto ((struct message *)&buf_rx)->Data;
        //cambiar imagen de boton
    }
    else if (instruction == -1)
    {
        printf("CLIENT: Son iguales \n");
        //objeto ((struct message *)&buf_rx)->Data;
        //cambiar imagen de boton
        //desabilitar las cartas
    } 
    else
    {
        printf("CLIENT: No son iguales \n");
        //objeto ((struct message *)&buf_rx)->Data;
        //cambiar imagen de boton
        //restaurar botones
    }
    
    
       
    /* close the socket */
    close(sockfd); 
    
    return 0;
} 