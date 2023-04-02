#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "player.hpp"

namespace ariel
{
    class Game
    {
    private:
    int remainingCards;
        Player p1;
        Player p2;

    public:
        Game(Player p1_, Player p2_);
        void playTurn();
        void printLastTurn();
        void playAll();    // playes the game untill the end
        void printWiner(); // prints the name of the winning player
        void printLog();   // prints all the turns played one line per turn (same format as void printLastTurn())
        void printStats();
        Player getP1();
        Player getP2();
    };
}

#endif