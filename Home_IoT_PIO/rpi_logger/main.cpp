#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include "serialMonitor.hpp"
#include "json.hpp"

#define LINE_BREAK "/////////////////////////////////////"

using json = nlohmann::json;

using namespace std;

//Prototype
string getSubstringBetweenDelimiters(string inputString, char startDelimiter, char endDelimiter);
string getTimeUTC();
json getJsonFromString(string input);

int main() {

    SerialMonitor sm;

    if(sm.init() == 0) {
        return(-1);
    }

    while(true) {

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

json getJsonFromString(string input) {

    json jsonData = json::parse(input);
    jsonData["DateTime"] = getTimeUTC();

    return(jsonData);

}