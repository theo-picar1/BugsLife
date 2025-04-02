#include "Crawler.h"

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

// Wall runs around the board (10x10) from 0-11, both x and y axes
bool Crawler::wayIsBlocked(Direction direction) {
    // If we are currently at position 10, The way ahead is blocked as the wall runs along 11.
    // The same for all if statements after this with minor changes to position.
    if (direction == Direction::NORTH && this->position.y == 10) {
        return true;
    }
    if (direction == Direction::WEST && this->position.x == 1) {
        return true;
    }
    if (direction == Direction::SOUTH && this->position.y == 1) {
        return true;
    }
    if (direction == Direction::EAST && this->position.x == 10) {
        return true;
    }

    return false;
}

void Crawler::move() {
    if (!this->wayIsBlocked(Direction::NORTH)) {
        this->direction = Direction::NORTH;
    } else if (!this->wayIsBlocked(Direction::EAST)) {
        this->direction = Direction::EAST;
    } else if (!this->wayIsBlocked(Direction::SOUTH)) { // TODO: Find out why this is always true
        this->direction = Direction::SOUTH;
    } else if (!this->wayIsBlocked(Direction::WEST)) {
        this->direction = Direction::WEST;
    }

    // Once done checking the unblocked paths, we initialise the new position
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
