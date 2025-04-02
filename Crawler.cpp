#include "Crawler.h"

#include <random>

Crawler::Crawler() {
    this->id = 0;
    this->position = {0, 0};
    this->direction = Direction::NORTH;
    this->size = 0;
    this->alive = true;
    this->path = {};
}

Crawler::Crawler(int id, Position position, Direction direction, int size, bool alive, list<Position> path) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = alive;
    this->path = path;
}

int Crawler::getId() const { return id; }

void Crawler::setId(int id) { this->id = id; }

Position Crawler::getPosition() const { return position; }

void Crawler::setPosition(Position position) { this->position = position; }

string Crawler::getDirection() const {
    switch (direction) {
        case Direction::NORTH:
            return "North";
        case Direction::WEST:
            return "West";
        case Direction::SOUTH:
            return "South";
        case Direction::EAST:
            return "East";
        default:
            return "Unknown";
    }
}

void Crawler::setDirection(Direction direction) { this->direction = direction; }

int Crawler::getSize() const { return size; }

void Crawler::setSize(int size) { this->size = size; }

bool Crawler::isAlive() const { return alive; }

void Crawler::setAlive(bool alive) { this->alive = alive; }

list<Position> Crawler::getPath() const { return path; }

void Crawler::setPath(list<Position> path) { this->path = path; }

// Anything below 0 or over 9 is considered out of bounds
bool Crawler::wayIsBlocked() {
    // If we are currently at position 9, The way ahead is blocked as outer bounds runs along 10.
    // The same for all if statements after this with minor changes to position.
    if (direction == Direction::NORTH && this->position.y == 9) {
        return true;
    }
    if (direction == Direction::WEST && this->position.x == 0) {
        return true;
    }
    if (direction == Direction::SOUTH && this->position.y == 0) {
        return true;
    }
    if (direction == Direction::EAST && this->position.x == 9) {
        return true;
    }

    return false;
}


void Crawler::move() {
    if (this->wayIsBlocked()) {
        // Reference: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 4);

        // distrib(gen) is the produced random number between 1 and 4 inclusive
        switch (distrib(gen)) {
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
    else {
        // Once done checking the unblocked paths, we initialise the new position with the current position
        Position nextPosition = this->position;

        // Continue to go in the direction that the bug is going in
        switch (this->direction) {
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
        this->path.push_back(nextPosition);
    }
}
