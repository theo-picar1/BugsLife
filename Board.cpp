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
        crawler->display();
    }
}

Crawler* Board::findBugById(int id)
{
    for (auto &crawler : crawlers)
    {
        if (crawler->getId() == id)
        {
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
    for(auto &crawler : crawlers) {	
        crawler->display();
        cout << "Path: ";
        for (auto &position : crawler->getPath()) {
            cout << "(" << position.x << ", " << position.y << "), ";
        }

        if(crawler->isAlive() == true) {
            cout << "Alive" << endl;
        }else {
            cout << "Eaten by " << crawler->getEatenBy() << endl;
        }
    }
}

string Board::getLifeHistory()
{
    string str = "";
    for(auto &crawler : crawlers) {	
        str += crawler->getDisplay();
        str += "Path: ";
        for (auto &position : crawler->getPath()) {
            str += "(" + to_string(position.x) + ", " + to_string(position.y) + "), ";
        }

        if(crawler->isAlive() == true) {
            str +=  "Alive";
        } else {
            str += "Eaten by " + to_string(crawler->getEatenBy());
        }
        str += "\n\n";
    }
    return str;
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
