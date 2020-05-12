#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include "serialMonitor.hpp"
#include "sample.cpp"  // Don't know why we need this...?  But the linker complains if we remove it.
#include "sample.hpp"
#include "json.hpp"

#define LINE_BREAK "//////////////////////////////"

using json = nlohmann::json;

using namespace std;

//Prototype
string getSubstringBetweenDelimiters(string inputString, char startDelimiter, char endDelimiter);
std::string escape_json(const std::string &s);

int main() {

    SerialMonitor sm;

    sm.init();

    while(true) {

        std::string data = sm.getData();

        if(data != ""){

            data = getSubstringBetweenDelimiters(data, '{', '}');

            cout << data << "Heuh" << endl;

            json jsonData = json::parse(data);

            cout << std::setw(8) << jsonData << endl;

            cout << jsonData["topic"] << endl;

            //Sample sample(jsonData["topic"], 69.696, "unit");

            //cout << sample << endl << LINE_BREAK << endl;

            cout << LINE_BREAK << endl;

        }

        usleep(DELAY*2);

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

std::string escape_json(const std::string &s) {
    std::ostringstream o;
    for (auto c = s.cbegin(); c != s.cend(); c++) {
        switch (*c) {
        case '"': o << "\\\""; break;
        case '\\': o << "\\\\"; break;
        case '\b': o << "\\b"; break;
        case '\f': o << "\\f"; break;
        case '\n': o << "\\n"; break;
        case '\r': o << "\\r"; break;
        case '\t': o << "\\t"; break;
        default:
            if ('\x00' <= *c && *c <= '\x1f') {
                o << "\\u"
                  << std::hex << std::setw(4) << std::setfill('0') << (int)*c;
            } else {
                o << *c;
            }
        }
    }
    return o.str();
}