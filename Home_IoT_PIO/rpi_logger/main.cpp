#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <sqlite3.h>
#include <signal.h>
#include "serialMonitor.hpp"
#include "json.hpp"

#define DATABASE_FILENAME   "meshlog.db"
#define LINE_BREAK          "////////////////////////////////////////"

using json = nlohmann::json;
using namespace std;

//Prototypes
string getSubstringBetweenDelimiters(string inputString, char startDelimiter, char endDelimiter);
string getTimeUTC();
string getDateTime();
json getJsonFromString(string input);
void doSQLInsert(json data);
void signalHandler(int sig);

//Global variables
volatile sig_atomic_t signalFlag = 0;
sqlite3* DB;

int main() {

    signal(SIGINT, signalHandler); // Tell program to call signalHandler() when SIGINT received

    SerialMonitor sm;

    if(sm.init() == 0) {
        cout << "Failed to open Serial Monitor!" << endl;
        return(-1);
    }

    int exit = sqlite3_open(DATABASE_FILENAME, &DB); 

    if(exit != SQLITE_OK) {
        cout << "Failed to open DB!" << endl;
        return(-1);
    }

    // Loop forever and ever.  (until SIGINT)
    while(true) {

        // Did we get a SIGINT?
        if(signalFlag) {
            cout << "--- SIGINT CAUGHT ---" << endl << "Closing DB and ending program..." << endl;
            sqlite3_close(DB);
            return(0);
        }

        std::string data = sm.getData();

        if(data != ""){

            data = getSubstringBetweenDelimiters(data, '{', '}');

            json jsonData = getJsonFromString(data);

            cout << std::setw(4) << jsonData << endl;

            cout << LINE_BREAK << endl;

            doSQLInsert(jsonData); // Where the magic happens

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

void doSQLInsert(json data) {

    int exit = 0;
    string query = "INSERT INTO Samples (DateTime, NodeID, Topic, Value, Unit) VALUES (" + to_string(data["DateTime"]) + ", " + to_string(data["nodeId"]) + ", " + to_string(data["topic"]) + ", " + to_string(data["value"]) + ", " + to_string(data["unit"]) + ");";
    char* errorMessage;
    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &errorMessage);

    cout << "*-*-*-*-*-*" << endl;

}

void signalHandler(int sig) {

    signalFlag = 1;

}