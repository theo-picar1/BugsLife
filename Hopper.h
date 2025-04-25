//
// Created by Theo Picar on 25/04/2025.
//

#ifndef HOPPER_H
#define HOPPER_H

#include "Bug.h"

using namespace std;

class Hopper : public Bug {
public :
    Hopper();

    Hopper(int id, Position position, Direction direction, int size, bool alive, int eatenBy, int hopLength);

    // The virtual method
    void move() override;

private:
    int hopLength;
};


#endif //HOPPER_H
