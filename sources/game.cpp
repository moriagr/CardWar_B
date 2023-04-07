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

    void Game::addLog(Card &cWinner, Card &cLoser, Player &winner, Player &loser)
    {
        // Alice played Queen of Hearts Bob played 5 of Spades. Alice wins.;
        string log = winner.getName() + " played " + cWinner.suit_to_string() + " of " + cWinner.rank_to_string();
        log = log + loser.getName() + " played " + cLoser.suit_to_string() + " of " + cLoser.rank_to_string() + ".";
        log = log + winner.getName() + " wins.";
        turnLog.push(log);
    }

    void Game::addWarLog(std::vector<Card> &cWinner, std::vector<Card> &cLoser, Player &winner, Player &loser)
    {
        string log = "";
        for (std::vector<Card>::size_type i = 0; i < cWinner.size(); i += 2)
        {

            // Alice played 6 of Hearts Bob played 6 of Spades. Draw. Alice played 10 of Clubs Bob played 10 of Diamonds. draw. Alice played Jack of Clubs Bob played King of Diamonds. Bob wins.
            log = log + winner.getName() + " played " + cWinner[i].suit_to_string() + " of " + cWinner[i].rank_to_string();
            log = log + loser.getName() + " played " + cLoser[i].suit_to_string() + " of " + cLoser[i].rank_to_string() + ".";
            if (i + 1 != cWinner.size())
            {
                log = log + " Draw.";
            }
            else
            {
                log = log + winner.getName() + " wins.";
            }
        }
        turnLog.push(log);
    }

    void Game::dealCards(std::vector<Card> &deck, Player &p1, Player &p2)
    {
        for (std::vector<Card>::size_type i = 0; i < 52; i++)
        {
            if (i % 2 == 0)
            {
                p1.addCardToStack(deck[i]);
            }
            else
            {
                p2.addCardToStack(deck[i]);
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
    // void Game::handleWar(Player p1, Player p2, int cardsToDraws)
    // {
    //     // Each player puts three cards face down, then one face up
    //     Card warCardsP1[4], warCardsP2[4];
    //     for (int i = 0; i < 4; i++)
    //     {
    //         if (p1.stacksize() < 1 || p2.stacksize() < 1)
    //         {
    //             return; // One of the players ran out of cards during the war
    //         }
    //         if (i < 3)
    //         {
    //             warCardsP1[i] = p1.drawCard();
    //             warCardsP2[i] = p2.drawCard();
    //         }
    //         else
    //         {
    //             warCardsP1[i] = p1.playCard();
    //             warCardsP2[i] = p2.playCard();
    //         }
    //     }

    //     // Check which player has the higher face-up card
    //     int result = compareCards(warCardsP1[3], warCardsP2[3]);
    //     if (result == 1)
    //     {
    //         // Player 1 wins the war, add all the war cards to their cardesTaken pile
    //         for (int i = 0; i < 4; i++)
    //         {
    //             p1.addCardToPile(warCardsP1[i]);
    //             p1.addCardToPile(warCardsP2[i]);
    //         }
    //     }
    //     else if (result == -1)
    //     {
    //         // Player 2 wins the war, add all the war cards to their cardesTaken pile
    //         for (int i = 0; i < 4; i++)
    //         {
    //             p2.addCardToPile(warCardsP1[i]);
    //             p2.addCardToPile(warCardsP2[i]);
    //         }
    //     }
    //     else
    //     {
    //         // Another war situation, recursively call handleWar()
    //         handleWar();
    //     }
    // }

    void Game::playTurn()
    {
        Card card1 = p1.takeCard();
        Card card2 = p2.takeCard();

        // Check if player1 got Ace and player2 got 2 - player2 one
        if (card1.GetRankValue() == 14 && card2.GetRankValue() == 2)
        {
            p2.addCardToTaken(card1);
            p2.addCardToTaken(card2);
            addLog(card2, card1, p2, p1);
        }
        // Check if player2 got Ace and player1 got 2 - player1 one
        else if (card2.GetRankValue() == 14 && card1.GetRankValue() == 2)
        {
            p1.addCardToTaken(card1);
            p1.addCardToTaken(card2);
            addLog(card1, card2, p1, p2);
        }
        // Player2 won
        else if (card2.GetRankValue() > card1.GetRankValue())
        {
            p2.addCardToTaken(card1);
            p2.addCardToTaken(card2);
            addLog(card2, card1, p2, p1);
        }
        // Player1 won
        else if (card2.GetRankValue() < card1.GetRankValue())
        {
            p1.addCardToTaken(card1);
            p1.addCardToTaken(card2);
            addLog(card1, card2, p1, p2);
        }

        // If there is war
        else
        {
            // while (p1.stacksize() / 2.0 > 0)
            // {
            //     // if (p1.stacksize() < 4 || player2->stacksize() < 4)
            //     // {
            //     //     return false;
            //     // }
            //     for (int i = 0; i < 3; i++)
            //     {
            //         wonCards.push_back(player1->takeCard());
            //         wonCards.push_back(player2->takeCard());
            //     }
            //     Card newCard1 = player1->takeCard();
            //     Card newCard2 = player2->takeCard();
            //     wonCards.push_back(newCard1);
            //     wonCards.push_back(newCard2);
            //     turnLog.push_back(make_pair(newCard1, newCard2));
            //     if (newCard1 > newCard2)
            //     {
            //         player1->addCard(card1);
            //         player1->addCard(card2);
            //         player1->addCard(newCard1);
            //         player1->addCard(newCard2);
            //         wonCards.push_back(card1);
            //         wonCards.push_back(card2);
            //         break;
            //     }
            //     else if (newCard2 > newCard1)
            //     {
            //         player2->addCard(card2);
            //         // player
            //     }
            // }
        }
    }

    void Game::printLastTurn()
    {
        if (turnLog.empty())
        {
            throw std::invalid_argument("We can't print log if you hav'nt played yet");
        }
        else
        {
            cout << turnLog.top() << endl;
        }
    }
    // playes the game until the end
    void Game::playAll()
    {
    }
    // prints the name of the winning player
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
            cout << "No Winner" << endl;
        }
    }

    void Game::printLog()
    {
        if (turnLog.empty())
        {
            throw std::invalid_argument("We can't print log if you hav'nt played yet");
        }
        else
        {
            std::stack<std::string> copyStack;
            while (!turnLog.empty())
            {
                copyStack.push(turnLog.top());
                turnLog.pop();
            }

            while (!copyStack.empty())
            {
                cout << copyStack.top() << endl;
                copyStack.pop();
            }
        }
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