#include "Board.h"
#include <iostream>

Board::Board() : Crawler_vector() {}

Board::Board(const vector<Crawler *> &Crawlers)
{
    Crawler_vector = Crawlers;
}

// Occupy the 10x10 board with Bugs from bug_vector
void Board::initializeBoard(vector<Crawler *> &crawlerVector)
{
    Crawler_vector = crawlerVector;
    if (Crawler_vector.empty())
    {
        cout << "bug board not initialized" << endl;
    }
}

void Board::displayAllBugs()
{
    for (auto &crawler : Crawler_vector)
    {
        cout << "ID: " << crawler->getId() << ", Position: (" << crawler->getPosition().getX() << ", " << crawler->getPosition().getY()
             << "), Direction: " << crawler->getDirection() << ", Size: " << crawler->getSize() << endl;
    }
}

void Board::findBugById()
{
}

void Board::tapBugBoard()
{
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
