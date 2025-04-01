#ifndef POSITION_H
#define POSITION_H

struct Position {
public:
    int x, y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    int getX() { return x; }
    int getY() { return y; }
};

#endif //POSITION_H


