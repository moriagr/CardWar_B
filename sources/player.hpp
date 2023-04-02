#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;
// #include "card.hpp"

namespace ariel
{

    class Player
    {
    private:
        int score;
        string name;
        // Card cArr[52];
        // Add an array that includes all the remaining cards that exists to the player - Im not sure if I need to do this right now or in onther time
    public:
        Player(std::string n);

        int stacksize();
        int cardesTaken();
        string getName();
        
    };
}
#endif