#include "Board.h"
#include <iostream>

Board::Board() : crawlers() {}

Board::Board(const vector<Crawler *> &crawlers)
{
    this->crawlers = crawlers;
}

// Occupy the 10x10 board with Bugs from bug_vector
void Board::initializeBoard(vector<Crawler *> &crawlers)
{
    this->crawlers = crawlers;
    if (crawlers.empty())
    {
        cout << "The bug board was not initialised" << endl;
    }
}

void Board::displayAllBugs()
{
    for (auto &crawler : crawlers)
    {
        cout << "ID: " << crawler->getId() << ", Position: (" << crawler->getPosition().getX() << ", " << crawler->getPosition().getY()
             << "), Direction: " << crawler->getDirection() << ", Size: " << crawler->getSize() << endl;
    }
}

Crawler* Board::findBugById(int id)
{
    for (auto &crawler : crawlers)
    {
        if (crawler->getId() == id)
        { // Assuming Crawler has a getId() function
            return crawler;
        }
    }
    return nullptr; // Return nullptr if the bug is not found

}

void Board::tapBugBoard()
{
    cout << "\nTapping the board..." << endl;

    for (int i = 0; i < this->crawlers.size(); ++i) {
        this->crawlers.at(i)->move();
    }

    cout << "New positions:" << endl;
    this->displayAllBugs();
}

void Board::displayLifeHistory()
{
}

void Board::displayAllCells()
{
}

void Board::runSimulation()
{
}

void Board::exit()
{
}
