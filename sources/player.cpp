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

    void Player::addCardToStack(const Card &card)
    {
        myStack.push_back(card);
        // for (std::vector<Card>::size_type i = 0; i < myStack.size(); i++)
        // {
        //     cout << "Player's cards:" << endl;
        //     myStack[i].printCard();
        // }
        // cout << myStack.size() << endl;
    }
    
    void Player::addCardToTaken(const Card &card)
    {
        myTaken.push_back(card);
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

    void Player::printCards()
    {
        cout << "Player's cards:" << endl;
        // cout << myStack.size() << endl;
        for (std::vector<Card>::size_type i = 0; i < myStack.size(); i++)
        {
            myStack[i].printCard();
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
        myTaken.push_back(card);
        return card;
    }
}