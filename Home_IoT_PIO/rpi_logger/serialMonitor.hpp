#include "rs232.h"

#define BUFLEN 79
#define COMPORT 16 // /dev/ttyUSB0
#define BAUD 115200
#define DELAY 10000000 // delay time; 10000000 us or 10 seconds.

// Function prototypes
char* distanceFromEnd(unsigned char* inputString, char inputChar);