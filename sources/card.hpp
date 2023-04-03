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
    public:
        enum class Suit
        {
            HEARTS,
            DIAMONDS,
            CLUBS,
            SPADES
        };
        enum class Rank
        {
            ACE = 1,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            TEN,
            JACK,
            QUEEN,
            KING
        };
        Card(Rank rank, Suit suit);
        int GetRankValue() const;
        Suit GetSuitValue() const;

    private:
        Rank myRank;
        Suit mySuit;
    };
}
#endif