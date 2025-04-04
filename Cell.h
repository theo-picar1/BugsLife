#ifndef CELL_H
#define CELL_H

#include <list>
#include "Crawler.h"

using namespace std;

class Cell {
private:
    int x, y;
    list<Crawler*> crawlers;

public:
    Cell();
    Cell(int x, int);

    // Getters
    int getX() const;
    int getY() const;
    list<Crawler*> getCrawlers() const;

    // Setters
    void setX(int id);
    void setY(int y);
    void setCrawlers(list<Crawler*> crawlers);

    // Methods
    void addCrawler(Crawler* crawler);
    void displayCrawlers();
    void clearCrawlers();
    void fightAndEat();
};



#endif //CELL_H
