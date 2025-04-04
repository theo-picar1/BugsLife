//
// Created by Theo Picar on 01/04/2025.
//

#ifndef BOARD_H
#define BOARD_H

#include "Crawler.h"
#include "Cell.h"
#include <vector>

class Board {
    vector<vector<Cell*>> board;

    vector<Crawler*> crawlers;

    Board(const vector<Crawler *> &crawlers);
public:
    Board();
    void initializeBoard(vector<Crawler*> &crawlers);
    void displayAllBugs();
    Crawler* findBugById(int id);
    void tapBugBoard();
    void displayLifeHistory();
    string getLifeHistory();
    void displayAllCells();
    void runSimulation();
    void exit();
    void displayBoard();
    Cell *getCell(int x, int y);
    void updateCells();
};

#endif //BOARD_H
