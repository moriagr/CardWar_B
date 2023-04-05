#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
using namespace std;

#include "game.hpp"
#include "player.hpp"
#include "card.hpp"

namespace ariel
{
    Game::Game(Player p1_, Player p2_) : p1(p1_), p2(p2_)
    {
        initializeGame(p1, p2);
    }

    void Game::initializeGame(Player &p1, Player &p2)
    {
        std::vector<Card> deck;
        for (int suit = 0; suit < 4; suit++)
        {
            for (int rank = 0; rank < 13; rank++)
            {
                Card card(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit));
                deck.push_back(card);
            }
        }
        shuffleDesk(deck);
        dealCards(deck, p1, p2);
        gameOver = false;
        p1.printCards();
    }
    void Game::dealCards(std::vector<Card> &deck, Player &p1, Player &p2)
    {
        for (std::vector<Card>::size_type i = 0; i < 52; i++)
        {
            if (i % 2 == 0)
            {
                p1.addCard(deck[i]);
            }
            else
            {
                p2.addCard(deck[i]);
            }
        }
    }
    void Game::shuffleDesk(std::vector<Card> &deck)
    {
        std::srand(std::time(nullptr));
        for (std::vector<Card>::size_type i = deck.size() - 1; i > 0; i--)
        {
            std::vector<Card>::size_type randIndex = (std::vector<Card>::size_type)std::rand() % (i + 1);
            Card temp = deck[i];
            deck[i] = deck[randIndex];
            deck[randIndex] = temp;
        }
    }
    void Game::handleWar(Player p1, Player p2, int cardsToDraws)
    {
    }

    void Game::playTurn()
    {
    }

    void Game::printLastTurn()
    {
    }

    void Game::playAll()
    {

    } // playes the game until the end
    void Game::printWiner()
    {
        if (p1.cardesTaken() > p2.cardesTaken())
        {
            cout << p1.getName() << endl;
        }
        else if (p1.cardesTaken() < p2.cardesTaken())
        {
            cout << p2.getName() << endl;
        }
        else
        {
            throw std::invalid_argument("We can't have a tie in the end");
        }

    } // prints the name of the winning player
    void Game::printLog()
    {

    } // prints all the turns played one line per turn (same format as void printLastTurn())
    void Game::printStats()
    {
    }

    Player Game::getP1()
    {
        return p1;
    }

    Player Game::getP2()
    {
        return p2;
    }
}