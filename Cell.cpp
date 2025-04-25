#include "Cell.h"
#include <iostream>
#include <random>

Cell::Cell()
{
    this->x = 0;
    this->y = 0;

    this->bugs = {};
}

Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;

    this->bugs = {};
};

int Cell::getX() const { return x; }

void Cell::setX(int x) { this->x = x; }

int Cell::getY() const { return y; }

void Cell::setY(int y) { this->y = y; }

list<Bug *> Cell::getBugs() const { return bugs; }

void Cell::setBugs(list<Bug *> bugs) { this->bugs = bugs; };

void Cell::addBug(Bug *bug)
{
    bugs.push_back(bug);
}

void Cell::displayBugs()
{
    if (this->bugs.size() > 0)
    {
        for (auto &bug : bugs)
        {
            bug->display();
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
    int maxSize = this->bugs.front()->getSize();
    for (auto bug : bugs) {
        if (bug->getSize() > maxSize) {
            maxSize = bug->getSize();
        }
    }

    // This is to check if there are any bugs that are the same size as each other.
    list<Bug*> biggestBugs;
    for (auto bug : bugs) {
        if (bug->getSize() == maxSize) {
            biggestBugs.push_back(bug);
        }
    }

    // Code to determine which bugs, that are the same size, will win
    Bug* winner = nullptr;
    if (biggestBugs.size() == 1) {
        winner = biggestBugs.front();
    }
    else {
        std::random_device rd;
        std::mt19937 gen(rd());
        // A random number will be generated between the ranges 0 and the number of bugs in the biggestBugs list
        std::uniform_int_distribution<> distr(0, biggestBugs.size() - 1);

        int index = distr(gen);
        auto it = biggestBugs.begin();
        std::advance(it, index);
        winner = *it;
    }

    // Set every other bug that isn't the winner to be dead and add their sizes to the winning bug
    for (auto bug : bugs) {
        if (bug != winner) {
            bug->setAlive(false);
            winner->grow(bug->getSize());
            bug->setEatenBy(winner->getId());
        }
    }

    cout << "Bug " << winner->getId() << " won and now has a size of " << winner->getSize() << endl;;
}

// To clear all bugs in a cell. This prevents stacking when calling Board::updateCells()
void Cell::clearBugs() {
    this->bugs.clear();
}
