#include "SuperBug.h"
#include "Board.h"

#include <random>

SuperBug::SuperBug() : Bug()
{
    this->type = "SuperBug";
    this->id = 0;
    this->position = {0, 0};
    this->direction = Direction::NORTH;
    this->size = 0;
    this->alive = true;
    this->eatenBy = -1;

    this->path = {};
}

SuperBug::SuperBug(int id, Position position, Direction direction, int size, bool alive, int eatenBy) : Bug()
{
    this->type = "SuperBug";
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = alive;
    this->eatenBy = eatenBy;

    this->path = list<Position>{this->position};
};

void SuperBug::move()
{
    Position nextPosition = this->position;

    // Reference: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 9);

    int x, y;
    do
    {
        x = distrib(gen);
        y = distrib(gen);
    } while (x == this->position.x && y == this->position.y);

    nextPosition.x = x;
    nextPosition.y = y;

    this->position = nextPosition;
    this->path.push_back(nextPosition); // Push the new position onto path for the bug's life history
}