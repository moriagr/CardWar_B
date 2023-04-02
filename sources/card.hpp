#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

namespace ariel
{

    class Card
    {
    private:
        string shape;
        int number;
        string name;
        // Add an array that includes all the remaining cards that exists to the Card - Im not sure if I need to do this right now or in onther time
    public:
        Card(string s, int num, string name);        
    };
}
#endif