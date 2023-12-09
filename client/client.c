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


#define HOSTNAME "localhost"
#define HOSTPORT "42069"

int client(){

    int socketfd;
    struct addrinfo hints;
    struct addrinfo *actualdata;
    int err, filefd;
    time_t ltime;

    /* choosing protocols */
    memset(&hints, 0, sizeof(hints)); // zero out memory
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;

    /* convert the address name into an IP address */
    err = getaddrinfo(HOSTNAME, HOSTPORT, &hints, &actualdata);
    if (err != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        exit(1);
    }

    // get a socket file descriptor to communicate with server
    socketfd = socket(actualdata->ai_family, actualdata->ai_socktype, 0);
    if (socketfd == -1){
        fprintf(stderr,"socket: %s\n", strerror(errno));
        exit(1);
    }

    printf("Connecting to %s:%s\n", HOSTNAME, HOSTPORT);

    // initiate the connection to the server
    err = connect(socketfd, actualdata->ai_addr, actualdata->ai_addrlen);
    if (err != 0){
        fprintf(stderr, "Error: connection failed -- %s\n", strerror(errno));
        exit(1);
    }



    // create a filename with the current time
    char filename[64];
    char *token;
    time(&ltime);
    char* time = ctime(&ltime);
    int j = 0;
    for (int i = 0; time[i]!='\0'; i++) {
        if (time[i] != ' ') {
            filename[j] = time[i];
            j++;
        }
    }

    filename[j-1] = '.';
    filename[j] = 't';
    filename[j+1] = 'x';
    filename[j+2] = 't';
    filename[j+3] = '\0';





    printf("Saving log to %s\n", filename);
    filefd = open(filename, O_CREAT | O_EXCL | O_TRUNC | O_RDWR, 0755); // create a new file, ADD USER PERMISSION FLAGS
    if (filefd < 0){
        fprintf(stderr, "Error: failed to open file\n");

    }
    ssize_t rd;
    char buffer[1024];
    while ((rd = read(socketfd, buffer, 1024)) > 0){
        ssize_t wr = write(filefd, buffer, rd);
    }

    close(filefd);
    printf("File download complete.\n");

    freeaddrinfo(actualdata);

    return 0;
}

int main(){
    client();
    return 0;
}