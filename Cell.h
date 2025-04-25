#ifndef CELL_H
#define CELL_H

#include <list>
#include "Bug.h"

using namespace std;

class Cell {
private:
    int x, y;
    list<Bug*> bugs;

public:
    Cell();
    Cell(int x, int);

    // Getters
    int getX() const;
    int getY() const;
    list<Bug*> getBugs() const;

    // Setters
    void setX(int id);
    void setY(int y);
    void setBugs(list<Bug*> bugs);

    // Methods
    void addBug(Bug* bug);
    void displayBugs();
    void clearBugs();
    void fightAndEat();
};



#endif //CELL_H
