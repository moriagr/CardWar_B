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
        void clearWarCards();
        void addCardToStack(const Card &card);
        void addCardToTaken(const Card &card);
        void printCards(const vector<Card> &cards);
        Card takeCard();
        vector<Card> getWarCards();
        void addCardToWar(const Card &card);
        vector<Card> getCardesTaken();
        float getWinRate() const;
        float getDrawRate() const;
        int getDraws() const;
        void increamentWins();
        void increamentDraw();
        void increamentLosses();
        void clearPlayer();

    private:
        string myName;
        vector<Card> myStack;
        vector<Card> myWarCards;
        vector<Card> myTaken;
        int wins = 0;
        int losses = 0;
        int draws = 0;
    };
}
#endif