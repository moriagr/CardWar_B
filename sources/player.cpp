#include <iostream>
// #include <fstream>
// #include <sstream>
// #include <stdexcept>
using namespace std;

#include "player.hpp"
namespace ariel
{

    Player::Player(std::string n)
    {
        this->name = n;
    };

    int Player::stacksize()
    {
        return 26;
    };
    int Player::cardesTaken()
    {
        return 0;
    };
    string Player::getName()
    {
        return name;
    }
}