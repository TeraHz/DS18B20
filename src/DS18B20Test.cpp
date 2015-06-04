/* Requests DS18B20 address, and prints current temperature to terminal.
Requires TeraHz's DS18B20 C++ library from here; https://github.com/TeraHz/DS18B20.git
To compile enter; g++ -Wall DS18B20Test.cpp DS18B20.cpp -o DS18B20Test
To run; ./DS18B20Test
*/

#include <iostream>
#include <string>
#include "DS18B20.h"
using namespace std;

int main() {
    double tempNow;
    char w1_address[16];
    
    cout << "Enter 1-Wire device address, including the '28-': ";
    cin >> w1_address;
    
    cout << "The address you entered was " << w1_address << endl;
    
    DS18B20 w1Device1 (w1_address);
    tempNow = w1Device1.getTemp();
    
    cout << "The current temperature is " << tempNow << " degrees Celsius" <<endl;
    
    return 0;
}