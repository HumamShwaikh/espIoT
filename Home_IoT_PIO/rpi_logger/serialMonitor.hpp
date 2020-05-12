#ifndef SERIALMONITOR_HPP
#define SERIALMONITOR_HPP

#include <iostream>
#include <string>
#include "rs232.h"

#define BUFLEN      111 // roughly matches the length of an incoming message
#define COMPORT     16 // /dev/ttyUSB0
#define BAUD        115200
#define DELAY       10000000 // delay time; 10000000 us or 10 seconds.


class SerialMonitor {



    public:
        unsigned char str_recv1[BUFLEN]; // recv data buffer 1
        unsigned char str_recv2[BUFLEN]; // recv data buffer 2
        int init();
        std::string getData();

};

#endif // SERIALMONITOR_HPP