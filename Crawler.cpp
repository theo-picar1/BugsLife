#include "Crawler.h"
#include "Board.h"

#include <random>
#include <iostream>
#include <print>

Crawler::Crawler() : Bug()
{
    this->type = "Crawler";
    this->id = 0;
    this->position = {0, 0};
    this->direction = Direction::NORTH;
    this->size = 0;
    this->alive = true;
    this->eatenBy = -1;

    this->path = {};
}

Crawler::Crawler(int id, Position position, Direction direction, int size, bool alive, int eatenBy) : Bug()
{
    this->type = "Crawler";
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = alive;
    this->eatenBy = eatenBy;

    this->path = list<Position>{this->position};
};

void Crawler::move()
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
    else
    {
        // Once done checking the unblocked paths, we initialise the new position with the current position
        Position nextPosition = this->position;

        // Continue to go in the direction that the bug is going in
        switch (this->direction)
        {
        case Direction::NORTH:
            nextPosition.y++;
            break;

        case Direction::EAST:
            nextPosition.x++;
            break;

        case Direction::SOUTH:
            nextPosition.y--;
            break;

        case Direction::WEST:
            nextPosition.x--;
            break;
        }

        this->position = nextPosition;
        this->path.push_back(nextPosition); // Push the new position onto path for the bug's life history
    }
}
