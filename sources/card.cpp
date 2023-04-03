#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "card.hpp"
namespace ariel
{
    Card::Card(Rank rank, Suit suit) : myRank(rank), mySuit(suit){};
    int Card::GetRankValue() const
    {
        switch (myRank)
        {
        case Rank::ACE:
            return 1;
        case Rank::TWO:
            return 2;
        case Rank::THREE:
            return 3;
        case Rank::FOUR:
            return 4;
        case Rank::FIVE:
            return 5;
        case Rank::SIX:
            return 6;
        case Rank::SEVEN:
            return 7;
        case Rank::EIGHT:
            return 8;
        case Rank::NINE:
            return 9;
        case Rank::TEN:
            return 10;
        case Rank::JACK:
            return 11;
        case Rank::QUEEN:
            return 12;
        case Rank::KING:
            return 13;
        default:
            throw std::logic_error("Unkown card rank");
        }
    }
    Card::Suit Card::GetSuitValue() const
    {
        return mySuit;
    }

}