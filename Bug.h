//
// Created by Theo Picar on 22/04/2025.
//

#ifndef BUG_H
#define BUG_H

#include <list>
#include <string>

using namespace std;

// 'enum class' instead of just 'enum' to prevent variables from being global
// Will be called as Direction::North rather than just NORTH
enum class Direction {
    NORTH = 1,
    WEST = 2,
    SOUTH = 3,
    EAST = 4
};

struct Position {
public:
    int x, y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    int getX() { return x; }
    int getY() { return y; }
};

class Bug {
protected:
    string type;
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    list<Position> path;
    int eatenBy;

public:
    Bug();
    Bug(int id, Position position, Direction direction, int size, bool alive, int eatenBy);

    // Getters
    int getId() const;
    Position getPosition() const;
    string getDirection() const;
    int getSize() const;
    bool isAlive() const;
    list<Position> getPath() const;
    int getEatenBy() const;

    // Setters
    void setId(int id);
    void setPosition(Position position);
    void setDirection(Direction direction);
    void setSize(int size);
    void setAlive(bool alive);
    void setPath(list<Position> path);
    void setEatenBy(int eatenBy);

    // Functions that all classes will have
    void display();
    string getDisplay();
    void grow(int growAmount);

    virtual void move();
    bool wayIsBlocked();
};



#endif //BUG_H
