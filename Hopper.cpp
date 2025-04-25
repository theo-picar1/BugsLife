#include "Hopper.h"
#include "Board.h"

#include <random>
#include <iostream>

Hopper::Hopper()
{
    this->type = "Hopper";
    this->id = 0;
    this->position = {0, 0};
    this->direction = Direction::NORTH;
    this->size = 0;
    this->alive = true;
    this->eatenBy = -1;
    this->path = {};
    this->hopLength = 2;
}

Hopper::Hopper(int id, Position position, Direction direction, int size, bool alive, int eatenBy, int hopLength)
{
    this->type = "Hopper";
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = alive;
    this->eatenBy = eatenBy;
    this->path = list<Position>{this->position};
    this->hopLength = hopLength;
};

void Hopper::move()
{
    if (this->wayIsBlocked())
    {
        // Reference: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 4);

        // distrib(gen) is the produced random number between 1 and 4 inclusive
        switch (distrib(gen))
        {
        case 1:
            this->direction = Direction::NORTH;
            break;
        case 2:
            this->direction = Direction::WEST;
            break;
        case 3:
            this->direction = Direction::SOUTH;
            break;
        case 4:
            this->direction = Direction::EAST;
            break;
        }

        this->move();
    }
    else // If the way is blocked, proceed to move normally
    {
        // Once done checking the unblocked paths, we initialise the new position with the current position
        Position nextPosition = this->position;

        // Continue to go in the direction that the bug is going in
        switch (this->direction)
        {
        case Direction::NORTH:
            // Ternary operator that will check for the following:
            // 1. If the current position on the y position is within less than hopLength distance from the wall, just set it just by the wall
            // 2. Otherwise, just move hopLength distance normally
            // 3. Logic applies to the other directions too
            nextPosition.y = (this->position.y > (9 - this->hopLength)) ? 9 : this->position.y + this-> hopLength;
            break;

        case Direction::EAST:
            nextPosition.x = (this->position.x > (9 - this->hopLength)) ? 9 : this->position.x + this-> hopLength;
            break;

        case Direction::SOUTH:
            // Same logic but in opposite direction
            nextPosition.y = (this->position.y < (0 + this->hopLength)) ? 0 : this->position.y - this-> hopLength;
            break;

        case Direction::WEST:
            nextPosition.x = (this->position.x < (0 + this->hopLength)) ? 0 : this->position.x - this-> hopLength;
            break;
        }

        this->position = nextPosition;
        this->path.push_back(nextPosition); // Push the new position onto path for the bug's life history
    }
}
