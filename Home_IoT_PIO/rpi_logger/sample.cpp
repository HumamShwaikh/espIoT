#include <iostream>
#include <ctime>
#include "sample.hpp"

using namespace std;

Sample::Sample(int _value, char _unit): value(_value), unit(_unit) {

    Sample::DateTime = time(NULL);  // Timestamp with current time

}