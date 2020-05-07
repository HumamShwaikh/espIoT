#include <iostream>
#include "serialMonitor.hpp"

using namespace std;

int main(){

    int comport = 16;  // /dev/ttyUSB0
    int baud = 115200;
    char mode[]={'8','N','1',0}; // 8 data bits, no parity, 1 stop bit

    unsigned char str_recv[BUFLEN]; // recv data buffer

    usleep(2000000);  /* waits 2000ms for stable condition */

    if(RS232_OpenComport(comport, baud, mode, 0)) {
        cout << "Can not open comport" << endl;
        return(0);
    }

    while(true){

        // Poll port for data
        int input = RS232_PollComport(comport, str_recv, (int)BUFLEN);
        if(input > 0) {
            str_recv[input] = 0;   /* always put a "null" at the end of a string! */
            printf("Received %i bytes: '%s'\n", input, (char *)str_recv);
            usleep(10000000);  /* sleep for 5 Second */

        }

        

    }

    return(0);

}