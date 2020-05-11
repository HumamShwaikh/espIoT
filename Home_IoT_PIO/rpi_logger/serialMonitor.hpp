#ifndef SERIALMONITOR_HPP
#define SERIALMONITOR_HPP

#include <iostream>
#include <string>
#include "rs232.h"

#define BUFLEN 79
#define COMPORT 16 // /dev/ttyUSB0
#define BAUD 115200
#define DELAY 5000000 // delay time; 5000000 us or 5 seconds.


class SerialMonitor {



    public:
        unsigned char str_recv1[BUFLEN]; // recv data buffer 1
        unsigned char str_recv2[BUFLEN]; // recv data buffer 2
        int init();
        std::string getData();

};

#endif // SERIALMONITOR_HPP