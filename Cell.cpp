#include "Cell.h"
#include <iostream>
#include <random>

Cell::Cell()
{
    this->x = 0;
    this->y = 0;

    this->crawlers = {};
}

Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;

    this->crawlers = {};
};

int Cell::getX() const { return x; }

void Cell::setX(int x) { this->x = x; }

int Cell::getY() const { return y; }

void Cell::setY(int y) { this->y = y; }

list<Crawler *> Cell::getCrawlers() const { return crawlers; }

void Cell::setCrawlers(list<Crawler *> crawlers) { this->crawlers = crawlers; };

void Cell::addCrawler(Crawler *crawler)
{
    crawlers.push_back(crawler);
}

void Cell::displayCrawlers()
{
    if (this->crawlers.size() > 0)
    {
        for (auto &crawler : crawlers)
        {
            crawler->display();
        }
    }
    else
    {
        cout << "Empty" << endl;
    }
}

// Method, when called (if statement done in Board.cpp), that will cause all bugs in a cell to fight.
void Cell::fightAndEat() {

    // First find the biggest bug in the cell
    int maxSize = this->crawlers.front()->getSize();
    for (auto crawler : crawlers) {
        if (crawler->getSize() > maxSize) {
            maxSize = crawler->getSize();
        }
    }

    // This is to check if there are any bugs that are the same size as each other.
    list<Crawler*> biggestCrawlers;
    for (auto crawler : crawlers) {
        if (crawler->getSize() == maxSize) {
            biggestCrawlers.push_back(crawler);
        }
    }

    // Code to determine which bugs, that are the same size, will win
    Crawler* winner = nullptr;
    if (biggestCrawlers.size() == 1) {
        winner = biggestCrawlers.front();
    }
    else {
        std::random_device rd;
        std::mt19937 gen(rd());
        // A random number will be generated between the ranges 0 and the number of bugs in the biggestCrawlers list
        std::uniform_int_distribution<> distr(0, biggestCrawlers.size() - 1);

        int index = distr(gen);
        auto it = biggestCrawlers.begin();
        std::advance(it, index);
        winner = *it;
    }

    // Set every other crawler that isn't the winner to be dead and add their sizes to the winning bug
    for (auto crawler : crawlers) {
        if (crawler != winner) {
            crawler->setAlive(false);
            winner->grow(crawler->getSize());
        }
    }

    cout << "Bug " << winner->getId() << " won and now has a size of " << winner->getSize() << endl;;
}

// To clear all crawlers in a cell. This prevents stacking when calling Board::updateCells()
void Cell::clearCrawlers() {
    this->crawlers.clear();
}
