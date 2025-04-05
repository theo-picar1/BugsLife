#ifndef CRAWLER_H
#define CRAWLER_H

#include <string>
#include <list>

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

class Crawler {
private:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    list<Position> path;
    int eatenBy;

public:
    Crawler();
    Crawler(int id, Position position, Direction direction, int size, bool alive, int eatenBy);

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
    void grow(int growAmount);

    void display();
    string getDisplay();

    void move();
    bool wayIsBlocked();
};



#endif //CRAWLER_H
