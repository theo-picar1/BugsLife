#ifndef CRAWLER_H
#define CRAWLER_H

#include "Position.h"

#include <string>
#include <list>

using namespace std;

class Crawler {
private:
    int id;
    Position position;
    int direction;
    int size;
    bool alive;
    list<Position> path;

public:
    Crawler();
    Crawler(int id, Position position, int direction, int size, bool alive, list<Position> path);

    // Getters
    int getId() const;
    Position getPosition() const;
    int getDirection() const;
    int getSize() const;
    bool isAlive() const;
    list<Position> getPath() const;

    // Setters
    void setId(int id);
    void setPosition(Position position);
    void setDirection(int direction);
    void setSize(int size);
    void setAlive(bool alive);
    void setPath(list<Position> path);

    void move();
    bool wayIsBlocked();
};



#endif //CRAWLER_H
