//
// Created by Theo Picar on 01/04/2025.
//

#ifndef BOARD_H
#define BOARD_H

#include "Crawler.h"
#include <vector>

class Board {
    vector<Crawler*> Crawler_vector;

    Board(const vector<Crawler *> &Crawlers);
public:
    Board();
    void initializeBoard(vector<Crawler*> &bcrawlers);
    void displayAllBugs();
    void findBugById();
    void tapBugBoard();
    void displayLifeHistory();
    void displayAllCells();
    void runSimulation();
    void exit();
};



#endif //BOARD_H
