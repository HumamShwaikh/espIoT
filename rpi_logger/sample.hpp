#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Sample {

    string dateTime;
    string topic;
    float value;
    string unit;

public:

    Sample(string _topic, float _value, string _unit);
    string getTimeUTC();
    friend std::ostream& operator<< (std::ostream &out, const Sample &sample);
};


#endif // SAMPLE_HPP