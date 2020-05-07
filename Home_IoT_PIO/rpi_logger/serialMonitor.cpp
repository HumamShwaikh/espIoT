#include <iostream>
#include "serialMonitor.hpp"

using namespace std;

int main(){

    int comport = 16;  // /dev/ttyUSB0
    int baud = 115200;
    char mode[]={'8','N','1',0}; // 8 data bits, no parity, 1 stop bit

    unsigned char str_recv1[BUFLEN]; // recv data buffer 1
    unsigned char str_recv2[BUFLEN]; // recv data buffer 2

    usleep(2000000);  /* waits 2000ms for stable condition */

    if(RS232_OpenComport(comport, baud, mode, 0)) {
        cout << "Can not open comport" << endl;
        return(0);
    }

    while(true){

        strncpy((char*)str_recv1, (char*)str_recv2, BUFLEN);  // Transfer content of new buffer into old buffer

        // Poll port for data
        int input = RS232_PollComport(comport, str_recv2, (int)BUFLEN);
        if(input > 0) {
            str_recv2[input] = 0;   /* always put a "null" at the end of a string! */

            if( strchr((char*)str_recv1, '<') != NULL && strchr((char*)str_recv1, '>') && strlen(strchr((char*)str_recv1, '<')) > strlen(strchr((char*)str_recv1, '>')) ) {
                // Print out content of str_recv1 between chars '<' and '>'
                printf("Yeceived %i bytes: '%s'\n", input, (char *)str_recv1);
            }
            else if( strchr((char*)str_recv1, '<') != NULL && strchr((char*)str_recv2, '>') ) {
                // Print out content of str_recv1 after char '<' and content of str_recv2 before char '>'
                printf("Zeceived %i bytes: '%s'\n and also %s\n", input, (char *)str_recv1, (char *)str_recv2);
            }

            //printf("Received %i bytes: '%s'\n", input, (char *)str_recv1);


            usleep(10000000);  /* sleep for 10 Second */

        }

        

    }

    return(0);

}

