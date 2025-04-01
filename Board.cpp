#include "Board.h"
#include <iostream>

Board::Board(const vector<Crawler*> &Crawlers) {
    Crawler_vector = Crawlers;
}

void Board::initializeBoard(vector<Crawler *> &crawlerVector) {
    Crawler_vector = crawlerVector;
    if(Crawler_vector.empty()){
        cout << "bug board not initialized" << endl;
    }
}

void Board::tapBugBoard() {

}

void Board::displayLifeHistory() {

}

void Board::displayAllCells() {

}

void Board::runSimulation() {

}

void Board::exit() {

}