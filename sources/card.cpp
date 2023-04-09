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
            return 14;
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

    string Card::rank_to_string()
    {
        switch (myRank)
        {
        case Card::Rank::TWO:
            return "Two";
        case Card::Rank::THREE:
            return "Three";
        case Card::Rank::FOUR:
            return "Four";
        case Card::Rank::FIVE:
            return "Five";
        case Card::Rank::SIX:
            return "Six";
        case Card::Rank::SEVEN:
            return "Seven";
        case Card::Rank::EIGHT:
            return "Eight";
        case Card::Rank::NINE:
            return "Nine";
        case Card::Rank::TEN:
            return "Ten";
        case Card::Rank::JACK:
            return "Jack";
        case Card::Rank::QUEEN:
            return "Queen";
        case Card::Rank::KING:
            return "King";
        case Card::Rank::ACE:
            return "Ace";
        default:
            return "";
        }
    }

    string Card::suit_to_string()
    {
        switch (mySuit)
        {
        case Card::Suit::HEARTS:
            return "HEARTS";
        case Card::Suit::DIAMONDS:
            return "DIAMONDS";
        case Card::Suit::CLUBS:
            return "CLUBS";
        case Card::Suit::SPADES:
            return "SPADES";
        default:
            return "";
        }
    }

    Card::Suit Card::GetSuitValue() const
    {
        return mySuit;
    }
    void Card::printCard()
    {
        cout << rank_to_string() << " of :" << suit_to_string() << endl;
    }
}