#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;
#include "card.hpp"

namespace ariel
{

    class Player
    {
    public:
        Player(std::string n);

        int stacksize();
        int cardesTaken();
        string getName();
        void addToStack(const vector<Card> &cards);
        void addCard(const Card &card);
        void printCards();

    private:
        string myName;
        int score;
        vector<Card> myStack;
        vector<Card> myTaken;
    };
}
#endif