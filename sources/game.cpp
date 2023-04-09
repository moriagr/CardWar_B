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
    Game::Game(Player &p1_, Player &p2_) : p1(p1_), p2(p2_)
    {
        initializeGame();
    }

    void Game::initializeGame()
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
        dealCards(deck);
        // gameOver = false;
        // p1.printCards();
    }

    void Game::addLog(Card &cWinner, Card &cLoser, Player &winner, Player &loser)
    {
        // Alice played Queen of Hearts Bob played 5 of Spades. Alice wins.;
        string log = winner.getName() + " played " + cWinner.rank_to_string() + " of " + cWinner.suit_to_string() + " ";
        log = log + loser.getName() + " played " + cLoser.rank_to_string() + " of " + cLoser.suit_to_string() + ". ";
        log = log + winner.getName() + " wins.";
        turnLog.push(log);
    }

    void Game::addWarLog(Player &winner, Player &loser)
    {
        string log = "";
        std::vector<Card> cWinner = winner.getWarCards();
        std::vector<Card> cLoser = loser.getWarCards();
        for (std::vector<Card>::size_type i = 0; i < cWinner.size(); i += 2)
        {

            // Alice played 6 of Hearts Bob played 6 of Spades. Draw. Alice played 10 of Clubs Bob played 10 of Diamonds. draw. Alice played Jack of Clubs Bob played King of Diamonds. Bob wins.
            log = log + winner.getName() + " played " + cWinner[i].rank_to_string() + " of " + cWinner[i].suit_to_string() + " ";
            log = log + loser.getName() + " played " + cLoser[i].rank_to_string() + " of " + cLoser[i].suit_to_string() + ". ";
            if (i + 1 != cWinner.size())
            {
                log = log + "Draw. ";
            }
            else
            {
                log = log + winner.getName() + " wins.";
            }
        }
        turnLog.push(log);
    }

    void Game::dealCards(std::vector<Card> &deck)
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

    void Game::playTurn()
    {
        if (&p1 == &p2)
        {
            throw std::invalid_argument("Same player");
        }
        if (p1.stacksize() == 0)
        {
            throw std::invalid_argument("We can't play turn beacause no card left");
        }
        Card card1 = p1.takeCard();
        Card card2 = p2.takeCard();

        // Check if player1 got Ace and player2 got 2 - player2 one
        if (card1.GetRankValue() == 14 && card2.GetRankValue() == 2)
        {
            p2.addCardToTaken(card1);
            p2.addCardToTaken(card2);
            p2.increamentWins();
            p1.increamentLosses();
            addLog(card2, card1, p2, p1);
            return;
        }
        // Check if player2 got Ace and player1 got 2 - player1 one
        else if (card2.GetRankValue() == 14 && card1.GetRankValue() == 2)
        {
            p1.addCardToTaken(card1);
            p1.addCardToTaken(card2);
            p1.increamentWins();
            p2.increamentLosses();
            addLog(card1, card2, p1, p2);
            return;
        }
        // Player2 won
        else if (card2.GetRankValue() > card1.GetRankValue())
        {
            p2.addCardToTaken(card1);
            p2.addCardToTaken(card2);
            p2.increamentWins();
            p1.increamentLosses();
            addLog(card2, card1, p2, p1);
            return;
        }
        // Player1 won
        else if (card2.GetRankValue() < card1.GetRankValue())
        {
            p1.addCardToTaken(card1);
            p1.addCardToTaken(card2);
            p1.increamentWins();
            p2.increamentLosses();
            addLog(card1, card2, p1, p2);
            return;
        }

        // If there is war
        else
        {
            p1.addCardToWar(card1);
            p2.addCardToWar(card2);
            while (p1.stacksize() > 1)
            {
                p1.increamentDraw();
                p2.increamentDraw();
                p1.addCardToWar(p1.takeCard());
                p2.addCardToWar(p2.takeCard());
                card1 = p1.takeCard();
                card2 = p2.takeCard();
                p1.addCardToWar(card1);
                p2.addCardToWar(card2);
                // Check if player1 got Ace and player2 got 2 - player2 one
                if (card1.GetRankValue() == 14 && card2.GetRankValue() == 2)
                {
                    addWarLog(p2, p1);
                    p2.addToTaken(p2.getWarCards());
                    p2.addToTaken(p1.getWarCards());
                    p2.clearWarCards();
                    p1.clearWarCards();
                    p2.increamentWins();
                    p1.increamentLosses();
                    return;
                }
                // Check if player2 got Ace and player1 got 2 - player1 one
                else if (card2.GetRankValue() == 14 && card1.GetRankValue() == 2)
                {
                    addWarLog(p1, p2);
                    p1.addToTaken(p1.getWarCards());
                    p1.addToTaken(p2.getWarCards());
                    p2.clearWarCards();
                    p1.clearWarCards();
                    p1.increamentWins();
                    p2.increamentLosses();
                    return;
                }
                // Player2 won
                else if (card2.GetRankValue() > card1.GetRankValue())
                {
                    addWarLog(p2, p1);
                    p2.addToTaken(p2.getWarCards());
                    p2.addToTaken(p1.getWarCards());
                    p2.clearWarCards();
                    p1.clearWarCards();
                    p2.increamentWins();
                    p1.increamentLosses();
                    return;
                }
                // Player1 won
                else if (card2.GetRankValue() < card1.GetRankValue())
                {
                    addWarLog(p1, p2);
                    p1.addToTaken(p1.getWarCards());
                    p1.addToTaken(p2.getWarCards());
                    p2.clearWarCards();
                    p1.clearWarCards();
                    p1.increamentWins();
                    p2.increamentLosses();
                    return;
                }
            }
            p1.addToTaken(p1.getWarCards());
            p2.addToTaken(p2.getWarCards());
            if (p1.stacksize() > 0)
            {
                p1.addCardToTaken(p1.takeCard());
                p2.addCardToTaken(p2.takeCard());
            }
            p2.clearWarCards();
            p1.clearWarCards();
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
        if (&p1 == &p2)
        {
            throw std::invalid_argument("Same player");
        }
        if (p1.stacksize() == 0)
        {
            throw std::invalid_argument("We can't play turn beacause no card left");
        }
        while (p1.stacksize() > 0)
        {
            playTurn();
        }
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

    // prints all the turns played one line per turn (same format as void printLastTurn())
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
    }

    // for each player prints basic statistics: win rate, cards won, <other stats you want to print>.
    // Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )
    // void Game::printStats()
    // {
    //     cout << "Player 1: Name : " << p1.getName() << " : " << endl;
    //     cout << "Win rate:  ";
    //     if (p1.cardesTaken() > p2.cardesTaken())
    //     {
    //         cout << 0.5 << endl;
    //     }
    //     else
    //     {
    //         cout << 0 << endl;
    //     }
    //     p1.printCards(p1.getCardesTaken());
    //     cout << "Num of cards won: " << p1.cardesTaken() << endl;
    //     cout << "" << endl;

    //     cout << "Player 2: Name : " << p2.getName() << " : " << endl;
    //     p2.printCards(p2.getCardesTaken());
    //     cout << "Win rate:  ";

    //     if (p1.cardesTaken() < p2.cardesTaken())
    //     {
    //         cout << 0.5 << endl;
    //     }
    //     else
    //     {
    //         cout << 0 << endl;
    //     }
    //     cout << "" << endl;
    //     cout << "The amout of draws that happand are: " << countWarDraw << endl;
    // }
    void Game::printStats()
    {
        cout << "Player1 stats:" << endl;

        cout << " - " << p1.getName() << ":" << endl;
        cout << "   Win rate: " << p1.getWinRate() * 100 << "%" << endl;
        cout << "   Cards won: " << endl;
        p1.printCards(p1.getCardesTaken());

        cout << "   Draw rate: " << p1.getDrawRate() * 100 << "%" << endl;
        cout << "   Draws: " << p1.getDraws() << endl;
        // Add any other stats you want to print here
        cout << "" << endl;
        cout << "Player2 stats:" << endl;

        cout << " - " << p2.getName() << ":" << endl;
        cout << "   Win rate: " << p2.getWinRate() * 100 << "%" << endl;
        cout << "   Cards won: " << endl;
        p2.printCards(p2.getCardesTaken());

        cout << "   Draw rate: " << p2.getDrawRate() * 100 << "%" << endl;
        cout << "   Draws: " << p2.getDraws() << endl;
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