#include <iostream>
// #include <fstream>
// #include <sstream>
// #include <stdexcept>
using namespace std;

#include "player.hpp"
#include "card.hpp"
namespace ariel
{

    Player::Player(std::string name) : myName(name), myStack(), myTaken(){};

    void Player::addToTaken(const vector<Card> &cards)
    {
        myTaken.insert(myTaken.end(), cards.begin(), cards.end());
    }

    void Player::addCardToStack(const Card &card)
    {
        myStack.push_back(card);
    }

    void Player::addCardToTaken(const Card &card)
    {
        myTaken.push_back(card);
    }

    void Player::addCardToWar(const Card &card)
    {
        myWarCards.push_back(card);
    }

    void Player::clearWarCards()
    {
        myWarCards.clear();
    }

    void Player::clearPlayer()
    {
        myTaken.clear();
        myWarCards.clear();
        myStack.clear();
        wins = 0;
        losses = 0;
        draws = 0;
    }

    vector<Card> Player::getWarCards()
    {
        return myWarCards;
    }

    int Player::stacksize()
    {
        return myStack.size();
    };

    int Player::cardesTaken()
    {
        return myTaken.size();
    };

    vector<Card> Player::getCardesTaken()
    {
        return myTaken;
    };

    string Player::getName()
    {
        return myName;
    }

    void Player::printCards(const vector<Card> &cards)
    {
        cout << "Player's cards:" << endl;
        for (std::vector<Card>::size_type i = 0; i < cards.size(); i++)
        {
            ((Card)cards[i]).printCard();
            // cout << "" << endl;
        }
    }

    // Returns the player's win rate
    float Player::getWinRate() const
    {
        int totalGames = wins + losses;
        if (totalGames == 0)
        {
            return 0.5; // Default win rate for a new player is 50%
        }
        return static_cast<float>(wins) / totalGames;
    }

    // Returns the player's draw rate
    float Player::getDrawRate() const
    {
        int totalGames = wins + losses + draws;
        if (totalGames == 0)
        {
            return 0.0; // Default draw rate for a new player is 0%
        }
        return static_cast<float>(draws) / totalGames;
    }

    // Returns the number of draws this player has had
    int Player::getDraws() const
    {
        return draws;
    }

    void Player::increamentWins()
    {
        wins++;
    }
    void Player::increamentDraw()
    {
        draws++;
    }
    void Player::increamentLosses()
    {
        losses++;
    }

    Card Player::takeCard()
    {
        if (myStack.empty())
        {
            throw out_of_range("Stack is empty");
        }
        Card card = myStack.back();
        myStack.pop_back();
        // myTaken.push_back(card);
        return card;
    }
}