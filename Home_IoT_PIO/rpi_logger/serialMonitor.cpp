#include "serialMonitor.hpp"

using namespace std;

    int SerialMonitor::init(){

        char mode[]={'8','N','1',0}; // 8 data bits, no parity, 1 stop bit

        usleep(2000000);  /* waits 2000ms for stable condition */

        if(RS232_OpenComport(COMPORT, BAUD, mode, 0)) {
            cout << "serialMonitor: Couldn't open serial port " << COMPORT << "." << endl;
            return(0);
        }

        return(1);

    }

    std::string SerialMonitor::getData() {

            strncpy((char*)str_recv1, (char*)str_recv2, BUFLEN);  // Transfer content of new buffer into old buffer

            // Poll port for data
            int input = RS232_PollComport(COMPORT, str_recv2, (int)BUFLEN);

            string receivedData;

            if(input > 0) {

                str_recv2[input] = 0;   /* always put a "null" at the end of a string! */

                std::string str1 = reinterpret_cast<const char*>(str_recv1);
                std::string str2 = reinterpret_cast<const char*>(str_recv2);

                int str1pos[3] = {str1.find('<'), str1.find('>'), str1.length()};
                int str2pos[3] = {str2.find('<'), str2.find('>'), str2.length()};

                if( str1pos[0] != string::npos && str1pos[1] != string::npos && str1pos[0] < str1pos[1] ) {
                    // Print content of str_recv1 if str_recv1 contains '<' and '>' in that order
                    cout << "Yeceived " << input << " bytes: " << str1 << endl;
                    receivedData = str1.substr(str1pos[0], str1pos[2] - str1pos[1] - str1pos[0]);
                }
                else if( str1pos[0] != string::npos && str2pos[0] != string::npos && str2pos[1] != string::npos ) {
                    // Print out content of str_recv1 after char '<' and content of str_recv2 before char '>'
                    cout << "Xeceived " << input << " bytes: " << str2 << " and also " << str1 << endl;
                    receivedData = str1.substr(str1pos[0]) + str2.substr(0, str2pos[1] + 1);
                }
                else if( str1pos[0] != string::npos && str1pos[1] != string::npos && str2pos[1] != string::npos ) {
                    // Print out content of str_recv1 after char '<' and content of str_recv2 before char '>'
                    cout << "Zeceived " << input << " bytes: " << str2 << " and also " << str1 << endl;
                    receivedData = str1.substr(str1pos[0]) + str2.substr(0, str2pos[1] + 1);
                }

            }
            else {
                receivedData = "\t---Nothing available.---";
            }

            return(receivedData);

        }