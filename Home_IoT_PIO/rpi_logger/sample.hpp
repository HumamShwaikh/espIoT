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

std::ostream& operator<< (std::ostream &out, const Sample &sample)
{
    out << "Point(" << sample.dateTime << ", " << sample.topic << ", " << sample.value << ")"; // actual output done here
 
    return out; // return std::ostream so we can chain calls to operator<<
}

#endif // SAMPLE_HPP