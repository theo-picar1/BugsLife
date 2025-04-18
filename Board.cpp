#include "Board.h"
#include <iostream>
#include <list>
#include <set>

Board::Board() : crawlers() {
}

Board::Board(const vector<Crawler *> &crawlers) {
    this->crawlers = crawlers;
}

// Occupy the 10x10 board with Bugs from bug_vector (assuming it is not empty)
void Board::initializeBoard(vector<Crawler *> &crawlers) {
    this->crawlers = crawlers;

    if (this->crawlers.empty()) {
        cout << "There are no crawlers to initialise the board with. Please create some crawlers!" << endl;
    }

    // Creates a board (10x10 2d vector)
    board.resize(10, vector<Cell *>(10));

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Create a new cell with position i and j
            board[i][j] = new Cell(i, j);
        }
    }
}

// Display property of every bug on the board: Their id, type, position, status, etc
void Board::displayAllBugs() {
    for (auto &crawler: crawlers) {
        crawler->display();
    }
}

// Method to find and display a with a given id
void Board::findBugById(int id) {
    for (auto &crawler: crawlers) {
        if (crawler->getId() == id) {
            cout << "Bug found!" << endl;
            crawler->display();
            return; // End the method since bug has already been found
        }
    }

    cout << "No bug found with an ID of " << id << ". Please try again!" << endl;
}

// Method that will cause all the bugs in the board to move by 1 cell
void Board::tapBugBoard() {
    vector<Crawler*> aliveCrawlers; // Keep track of all alive crawlers to avoid double isAlive check

    cout << "\nTAPPING THE BOARD...\n";
    for (auto &crawler : crawlers) {
        if (crawler->isAlive()) {
            crawler->move();
            aliveCrawlers.push_back(crawler);
        }
    }

    cout << "NEW POSITIONS:\n";
    for (auto &crawler : aliveCrawlers) { // Only show the positions of all the alive crawlers
        crawler->display();
    }

    updateCells();
}


// Method to display all the cells with any crawlers on the board
void Board::displayBoard() {
    updateCells();

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << "Cell (" << i << ", " << j << "): ";
            board[i][j]->displayCrawlers(); // Display all the crawlers in that cell if any
        }
        cout << endl;
    }
}

// Displays life history of every bug. The path they took, who they were eaten by, their status and more...
void Board::displayLifeHistory() {
    for (auto &crawler: crawlers) {
        crawler->display();

        cout << "Path: ";
        for (auto &position: crawler->getPath()) {
            cout << "(" << position.x << ", " << position.y << "), ";
        }

        if (crawler->isAlive()) {
            cout << "Alive" << endl;
        }
        else {
            cout << "Eaten by " << crawler->getEatenBy() << endl;
        }
    }
}

// Similar to displayLifeHistory(). Only difference is we append it to a string and return that string.
string Board::getLifeHistory() {
    // All code logic here is just appending to 'str', where str is the content that will be written to the txt file
    string str = "";
    for (auto &crawler: crawlers) {
        str += crawler->getDisplay();
        str += "Path: ";
        for (auto &position: crawler->getPath()) {
            str += "(" + to_string(position.x) + ", " + to_string(position.y) + "), ";
        }

        if (crawler->isAlive() == true) {
            str += "Alive";
        } else {
            str += "Eaten by " + to_string(crawler->getEatenBy());
        }
        str += "\n\n";
    }
    return str;
}

// Method that will constantly tap, update and display the board until there is one bug left standing
void Board::runSimulation() {
    int leftAlive = 0;

    // Keep going as long as there are more than one bug alive
    while (leftAlive != 1) {
        tapBugBoard();

        // Reset the counter and then count again in for loop below
        leftAlive = 0;

        // Logic to count all the bugs that are still alive on the board
        for (auto &crawler: crawlers) {
            if (crawler->isAlive()) {
                leftAlive++;
            }
        }

        if (leftAlive > 1) {
            cout << "There are currently " << leftAlive << " bugs left on the board!" << endl;
        }
    }

    // Print the winner, who is the only remaining alive bug
    for (auto &crawler: crawlers) {
        if (crawler->isAlive()) {
            cout << "***** WINNER IS BUG " << crawler->getId() << ", AND IS " << crawler->getSize() <<
                    " POINTS LARGE! *****" << endl;
            cout << endl;
        }
    }
}

// Returns a pointer to the memory address of board[x][y].
Cell *Board::getCell(int x, int y) {
    return board[x][y];
}

// Code that, whenever called, will add crawlers to the cells in the board with the same depending on crawler positions
void Board::updateCells() {
    // Clear crawler lists from each cell to prevent stacking
    for (auto &crawler: crawlers) {
        int i = crawler->getPosition().getX();
        int j = crawler->getPosition().getY();

        board[i][j]->clearCrawlers();
    }


    int fightsOccured = 0; // Just for message purposes
    cout << "\nFIGHT LOG" << endl;

    // Adding crawler to a cell and fighting logic occurs in below for loop
    for (auto &crawler: crawlers) {
        // Get the cell that is equal to the current crawler's i and j position
        Cell *cell = getCell(crawler->getPosition().x, crawler->getPosition().y);

        // Then add that crawler to the cell object, only if it is alive
        if (crawler->isAlive()) {
            cell->addCrawler(crawler);
        }
    }

    set<Cell*> processedCells;
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            Cell* cell = getCell(x, y);
            if (cell->getCrawlers().size() > 1 && processedCells.find(cell) == processedCells.end()) { // Only proceed if the cell hasn't been processes yet
                cout << "A FIGHT IS OCCURRING AT CELL (" << x << ", " << y << ")" << endl;
                cell->fightAndEat();
                processedCells.insert(cell);
                fightsOccured++;
            }
        }
    }

    if (fightsOccured <= 0) {
        cout << "No bugs have fought or eaten each other during this tap!" << endl;
    }
}
