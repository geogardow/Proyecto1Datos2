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

int main(int argc, char const *argv[])
{
    client c = client();
    c.request.ID = 11;
    c.sendRequest(c.request);
    return 0;
}


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
    write(sockfd, (struct message *)&buf_tx, sizeof(buf_tx));     
    read(sockfd, (struct message *)&buf_rx, sizeof(buf_rx));
    printf("CLIENT:Received: %d \n", ((struct message *)&buf_rx)->ID);
       
    /* close the socket */
    close(sockfd); 
    
    return 0;
} 