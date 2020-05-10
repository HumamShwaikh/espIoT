#include <iostream>
#include <string>
#include "serialMonitor.hpp"
#include "sample.hpp"

using namespace std;

int main() {

    SerialMonitor sm;

    sm.init();

    while(true) {

        string data = sm.getData();

        cout << data << endl << endl;

        cout << "//////////////////////////////" << endl;

        usleep(DELAY/2);

    }









    return(0);
}