#include <iostream>
#include <string>
#include <algorithm>
#include "serialMonitor.hpp"
#include "sample.cpp"
#include "sample.hpp"
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

//Prototype
string getSubstringBetweenDelimiters(string inputString, char startDelimiter, char endDelimiter);

int main() {

    SerialMonitor sm;

    sm.init();

    while(true) {

        string data = sm.getData();

        if(data != ""){

            data = getSubstringBetweenDelimiters(data, '{', '}');

            json jsonData = data;

            Sample sample("topic", 69.696, "unit");

            cout << sample << endl;

            cout << "//////////////////////////////" << endl;

        }

        usleep(DELAY/2);

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