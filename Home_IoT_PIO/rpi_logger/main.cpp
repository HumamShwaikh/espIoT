#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <sqlite3.h>
#include <signal.h>
#include "serialMonitor.hpp"
#include "json.hpp"

#define LINE_BREAK "////////////////////////////////////////"

using json = nlohmann::json;
using namespace std;

//Prototypes
string getSubstringBetweenDelimiters(string inputString, char startDelimiter, char endDelimiter);
string getTimeUTC();
string getDateTime();
json getJsonFromString(string input);
void initDB();
void signalHandler(int sig);

//Global variables
volatile sig_atomic_t signalFlag = 0;

int main() {

    signal(SIGINT, signalHandler); // Tell program to call signalHandler() when SIGINT received

    SerialMonitor sm;

    if(sm.init() == 0) {
        cout << "Failed to open Serial Monitor!" << endl;
        return(-1);
    }

    // if(initDB() == 0) {
    //     cout << "Failed to open DB!" << endl;
    //     return(-1);
    // }

    // Loop forever and ever.  (until SIGINT)
    while(true) {

        // Did we get a SIGINT?
        if(signalFlag) {
            cout << "--- SIGINT CAUGHT ---" << endl << "Closing DB and ending program..." << endl;
            //Close Database Here
            return(0);
        }

        std::string data = sm.getData();

        if(data != ""){

            data = getSubstringBetweenDelimiters(data, '{', '}');

            json jsonData = getJsonFromString(data);

            cout << std::setw(4) << jsonData << endl;

            cout << LINE_BREAK << endl;

        }

        usleep(DELAY);

    }



    return(0);
}

/**
 * Takes a string and returns the substring betwen two given delimiters.
 * @param inputString
 * @param startDelimiter
 * @param endDelimiter
 * @return the truncated string
 **/
string getSubstringBetweenDelimiters(string inputString, char startDelimiter, char endDelimiter) {

    if(inputString.find(startDelimiter) == string::npos || inputString.find(endDelimiter) == string::npos){
        return(inputString);
    }
    
    unsigned int first = inputString.find(startDelimiter);
    unsigned int last = inputString.find(endDelimiter);

    return inputString.substr(first, last - first + 1);

}

/**
 * @return the current UTC time as a string.
 **/
string getTimeUTC() {

    time_t currentTime = time(NULL);
    string stringTime = ctime(&currentTime);



    return(stringTime.substr(0, stringTime.length() - 1));

}

/**
 * @return the current ISO 8601 date and time as a string.
 **/
string getDateTime() {

    time_t now;
    time(&now);
    char buf[30];
    strftime(buf, sizeof buf, "%Y-%m-%d %H:%M:%S", localtime(&now));
    std::string timestr(buf);

    return (timestr);

}

json getJsonFromString(string input) {

    json jsonData = json::parse(input);
    jsonData["DateTime"] = getDateTime();

    return(jsonData);

}

void initDB() {

    sqlite3* DB;

}

void signalHandler(int sig) {

    signalFlag = 1;

}