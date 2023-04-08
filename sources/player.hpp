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
        void addToTaken(const vector<Card> &cards);
        void addCardToStack(const Card &card);
        void addCardToTaken(const Card &card);
        void printCards();
        Card takeCard();
        vector<Card> getWarCards();
        void addCardToWar(const Card &card);

    private:
        string myName;
        int score;
        vector<Card> myStack;
        vector<Card> myWarCards;
        vector<Card> myTaken;
    };
}
#endif