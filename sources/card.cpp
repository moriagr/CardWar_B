#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "card.hpp"
namespace ariel
{
    Card::Card(string s, int num, string name)
    {
        this->shape = s;
        this->number = num;
        this->name = name;
    }; 
}