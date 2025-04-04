#include "Board.h"
#include <iostream>
#include <list>

Board::Board() : crawlers() {}

Board::Board(const vector<Crawler *> &crawlers)
{
    this->crawlers = crawlers;
}

// Occupy the 10x10 board with Bugs from bug_vector (assuming it is not empty)
void Board::initializeBoard(vector<Crawler *> &crawlers)
{
    this->crawlers = crawlers;

    if (crawlers.empty())
    {
        cout << "There are no crawlers to initialise the board with. Please create some crawlers!" << endl;
    }

    // Creates a board (10x10 2d vector)
    board.resize(10, vector<Cell *>(10));

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            // Create a new cell with position i and j
            board[i][j] = new Cell(i, j);
        }
    }
}

// Returns a pointer to the memory address of board[x][y]
Cell* Board::getCell(int x, int y)
{
    return board[x][y];
}

// Code that, whenever called, will add crawlers to the cells in the board with the same depending on crawler positions
void Board::updateCells() {
    // Clear crawler lists from each cell to prevent stacking
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            board[i][j]->clearCrawlers();
        }
    }

    for(auto &crawler : crawlers){
        // Get the cell that is equal to the current crawler's i and j position
        Cell* cell = getCell(crawler->getPosition().x, crawler->getPosition().y);

        // Then add that crawler to the cell object
        if (crawler->isAlive()) {
            cell->addCrawler(crawler);
        }

        if (cell->getCrawlers().size() > 1) {
            cell->fightAndEat();
        }
    }
}

void Board::displayBoard()
{

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            cout << "Cell (" << i << ", " << j << "): ";
            board[i][j]->displayCrawlers(); // Display all the crawlers in that cell if any
        }
        cout << endl;
    }
}

// Display property of every bug on the board: Their id, type, position, status, etc
void Board::displayAllBugs()
{
    for (auto &crawler : crawlers)
    {
        crawler->display();
    }
}

Crawler *Board::findBugById(int id)
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

    for (int i = 0; i < this->crawlers.size(); ++i)
    {
        this->crawlers.at(i)->move(); // Move functionality that is handled in the crawler class
    }

    cout << "New positions:" << endl;
    this->displayAllBugs();

    updateCells();
}

// Displays life history of every bug. The path they took, who they were eaten by, their status and more...
void Board::displayLifeHistory()
{
    for (auto &crawler : crawlers)
    {
        crawler->display();
        cout << "Path: ";
        for (auto &position : crawler->getPath())
        {
            cout << "(" << position.x << ", " << position.y << "), ";
        }

        if (crawler->isAlive() == true)
        {
            cout << "Alive" << endl;
        }
        else
        {
            cout << "Eaten by " << crawler->getEatenBy() << endl;
        }
    }
}

// Similar to displayLifeHistory(). Only difference is we append it to a string and return that string.
string Board::getLifeHistory()
{
    string str = "";
    for (auto &crawler : crawlers)
    {
        str += crawler->getDisplay();
        str += "Path: ";
        for (auto &position : crawler->getPath())
        {
            str += "(" + to_string(position.x) + ", " + to_string(position.y) + "), ";
        }

        if (crawler->isAlive() == true)
        {
            str += "Alive";
        }
        else
        {
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
