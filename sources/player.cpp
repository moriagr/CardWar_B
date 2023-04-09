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
            cout << "" << endl;
        }
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