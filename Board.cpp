#include "Board.h"
#include <iostream>
#include <list>
#include <set>

Board::Board() : bugs() {
}

Board::Board(const vector<Bug *> &bugs) {
    this->bugs = bugs;
}

// Occupy the 10x10 board with Bugs from bug_vector (assuming it is not empty)
void Board::initializeBoard(vector<Bug *> &bugs) {
    this->bugs = bugs;

    if (this->bugs.empty()) {
        cout << "There are no bugs to initialise the board with. Please create some bugs!" << endl;
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
    for (auto &bug: bugs) {
        bug->display();
    }
}

// Method to find and display a with a given id
void Board::findBugById(int id) {
    for (auto &bug: bugs) {
        if (bug->getId() == id) {
            cout << "Bug found!" << endl;
            bug->display();
            return; // End the method since bug has already been found
        }
    }

    cout << "No bug found with an ID of " << id << ". Please try again!" << endl;
}

// Method that will cause all the bugs in the board to move by 1 cell
void Board::tapBugBoard() {
    vector<Bug*> aliveBugs; // Keep track of all alive bugs to avoid double isAlive check

    cout << "\nTAPPING THE BOARD...\n";
    for (auto &bug : bugs) {
        if (bug->isAlive()) {
            cout << "Bug " << bug->getId() << " is moving...\n";
            bug->move();
            aliveBugs.push_back(bug);
        }
    }

    cout << "NEW POSITIONS:\n";
    for (auto &bug : aliveBugs) { // Only show the positions of all the alive bugs
        bug->display();
    }

    updateCells();
}


// Method to display all the cells with any bugs on the board
void Board::displayBoard() {
    updateCells();

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << "Cell (" << i << ", " << j << "): ";
            board[i][j]->displayBugs(); // Display all the bugs in that cell if any
        }
        cout << endl;
    }
}

// Displays life history of every bug. The path they took, who they were eaten by, their status and more...
void Board::displayLifeHistory() {
    for (auto &bug: bugs) {
        bug->display();

        cout << "Path: ";
        for (auto &position: bug->getPath()) {
            cout << "(" << position.x << ", " << position.y << "), ";
        }

        if (bug->isAlive()) {
            cout << "Alive" << endl;
        }
        else {
            cout << "Eaten by " << bug->getEatenBy() << endl;
        }
    }
}

// Similar to displayLifeHistory(). Only difference is we append it to a string and return that string.
string Board::getLifeHistory() {
    // All code logic here is just appending to 'str', where str is the content that will be written to the txt file
    string str = "";
    for (auto &bug: bugs) {
        str += bug->getDisplay();
        str += "Path: ";
        for (auto &position: bug->getPath()) {
            str += "(" + to_string(position.x) + ", " + to_string(position.y) + "), ";
        }

        if (bug->isAlive() == true) {
            str += "Alive";
        } else {
            str += "Eaten by " + to_string(bug->getEatenBy());
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
        for (auto &bug: bugs) {
            if (bug->isAlive()) {
                leftAlive++;
            }
        }

        if (leftAlive > 1) {
            cout << "There are currently " << leftAlive << " bugs left on the board!" << endl;
        }
    }

    // Print the winner, who is the only remaining alive bug
    for (auto &bug: bugs) {
        if (bug->isAlive()) {
            cout << "***** WINNER IS BUG " << bug->getId() << ", AND IS " << bug->getSize() <<
                    " POINTS LARGE! *****" << endl;
            cout << endl;
        }
    }
}

// Returns a pointer to the memory address of board[x][y].
Cell *Board::getCell(int x, int y) {
    return board[x][y];
}

// Code that, whenever called, will add bugs to the cells in the board with the same depending on bug positions
void Board::updateCells() {
    // Clear bug lists from each cell to prevent stacking
    for (auto &bug: bugs) {
        int i = bug->getPosition().getX();
        int j = bug->getPosition().getY();

        board[i][j]->clearBugs();
    }


    int fightsOccured = 0; // Just for message purposes
    cout << "\nFIGHT LOG" << endl;

    // Adding bug to a cell and fighting logic occurs in below for loop
    for (auto &bug: bugs) {
        // Get the cell that is equal to the current bug's i and j position
        Cell *cell = getCell(bug->getPosition().x, bug->getPosition().y);

        // Then add that bug to the cell object, only if it is alive
        if (bug->isAlive()) {
            cell->addBug(bug);
        }
    }

    set<Cell*> processedCells;
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            Cell* cell = getCell(x, y);
            if (cell->getBugs().size() > 1 && processedCells.find(cell) == processedCells.end()) { // Only proceed if the cell hasn't been processes yet
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
