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
#define SERV_HOST_ADDR "192.168.3.105" /* IP, only IPV4 support  */
#define BACKLOG 5                      /* Max. client pending connections  */

int main(int argc, char const *argv[])
{
    server s = server();
    s.start();
    return 0;
}

server::server()
{
}

int server::start()
{

    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        fprintf(stderr, "[SERVER-error]: socket creation failed. %d: %s \n", errno, strerror(errno));
        return -1;
    }
    else
    {
        printf("[SERVER]: Socket successfully created..\n");
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
        fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n", errno, strerror(errno));
        return -1;
    }
    else
    {
        printf("[SERVER]: Socket successfully binded \n");
    }

    while (1){

        /* Listen */
        if ((listen(sockfd, BACKLOG)) != 0)
        {
            fprintf(stderr, "[SERVER-error]: socket listen failed. %d: %s \n", errno, strerror(errno));
            return -1;
        }
        else
        {
            printf("[SERVER]: Listening on SERV_PORT %d \n\n", ntohs(servaddr.sin_port));
        }

        len = sizeof(client);

        /* Accept the data from incoming sockets in a iterative way */
    
        connfd = accept(sockfd, (struct sockaddr *)&client, &len);
        if (connfd < 0)
        {
            fprintf(stderr, "[SERVER-error]: connection not accepted. %d: %s \n", errno, strerror(errno));
            return -1;
        }
        else
        {
            printf("[SERVER]: connfd was read successfully \n\n");
            while (1) /* read data from a client socket till it is closed */
            {
                /* read client message, copy it into buffer */
                len_rx = read(connfd, (char *)&buff_rx, sizeof(buff_rx));

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
                    buff_tx.ID=20;
                    write(connfd, (struct message *)&buff_tx, sizeof(buff_tx));
                    printf("[SERVER]: %d \n", ((struct message *)&buff_rx)->ID);
                    close(connfd);
                    break;
                }
            }
        }
    }
}