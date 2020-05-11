#include "sample.hpp"

using namespace std;

Sample::Sample(string _topic, float _value, string _unit) {

    Sample::dateTime = getTimeUTC();  // Timestamp with current date & time
    Sample::topic = _topic;
    Sample::value = _value;
    Sample::unit = _unit;
}

string Sample::getTimeUTC() {

    time_t currentTime = time(NULL);
    string stringTime = ctime(&currentTime);

    return(stringTime);

}

std::ostream& operator<< (std::ostream &out, const Sample &sample) {

    out << "Sample(" << sample.dateTime << " | " << sample.topic << " | " << sample.value << sample.unit << ")";
 
    return out; // return std::ostream so we can chain calls to operator<<

}


