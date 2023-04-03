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

    void Player::addToStack(const vector<Card> &cards)
    {
        myStack.insert(myStack.end(), cards.begin(), cards.end());
    }
    void Player::addCard(const Card &card)
    {
        myStack.push_back(card);
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
}