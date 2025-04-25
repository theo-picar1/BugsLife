#ifndef SUPERBUG_H
#define SUPERBUG_H

#include "Bug.h"
#include <string>

using namespace std;

class SuperBug : public Bug
{

public:
    SuperBug();
    SuperBug(int id, Position position, Direction direction, int size, bool alive, int eatenBy);

    // The virtual method
    void move() override;
};

#endif // SUPERBUG_H
