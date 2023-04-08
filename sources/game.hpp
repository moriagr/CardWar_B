#ifndef GAME_H
#define GAME_H

#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "player.hpp"

namespace ariel
{
    class Game
    {
    private:
        Player p1;
        Player p2;
        std::vector<Card> centerDeck;
        std::vector<Card> spoilsOfWar;
        std::stack<std::string> turnLog;
        bool gameOver;
        bool war;
        void initializeGame(Player &p1, Player &p2);
        void shuffleDesk(std::vector<Card> &deck);
        void dealCards(std::vector<Card> &deck, Player &p1, Player &p2);
        void addLog(Card &cWinner, Card &cLoser, Player &winner, Player &loser);
        void addWarLog(Player &winner, Player &loser);
        void handleWar(Player p1, Player p2, int cardsToDraws);

    public:
        Game(Player p1_, Player p2_);
        void playTurn();
        void printLastTurn();
        void playAll();    // playes the game untill the end
        void printWiner(); // prints the name of the winning player
        void printLog();   // prints all the turns played one line per turn (same format as void printLastTurn())
        void printStats();
        Player getP1();
        Player getP2();
    };
}

#endif