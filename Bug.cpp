//
// Created by Theo Picar on 22/04/2025.
//

#include "Bug.h"
#include <iostream>

using namespace std;

Bug::Bug() {
    id = 0;
    position = Position(0, 0);
    direction = Direction::NORTH;
    size = 1;
    alive = true;
    eatenBy = -1;
}

int Bug::getId() const { return id; }

void Bug::setId(int id) { this->id = id; }

Position Bug::getPosition() const { return position; }

void Bug::setPosition(Position position) { this->position = position; }

string Bug::getDirection() const {
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

void Bug::setDirection(Direction direction) { this->direction = direction; }

int Bug::getSize() const { return size; }

void Bug::setSize(int size) { this->size = size; }

bool Bug::isAlive() const { return alive; }

void Bug::setAlive(bool alive) { this->alive = alive; }

list<Position> Bug::getPath() const { return path; }

void Bug::setPath(list<Position> path) { this->path = path; }

int Bug::getEatenBy() const { return eatenBy; }

void Bug::setEatenBy(int eatenBy) { this->eatenBy = eatenBy; }

void Bug::display(){
    cout << "ID: " << id << ", Position: (" << position.x << ", " << position.y
             << "), Direction: " << this->getDirection() << ", Size: " << size << endl;
}

string Bug::getDisplay(){
    return "ID: " + to_string(id) + "\nPosition: (" + to_string(position.x) + ", " + to_string(position.y) + ")\nDirection: " + this->getDirection() + "\nSize: " + to_string(size) + "\n";
}

// This method will be overrided by the other classes
void Bug::move() {

}

// Anything below 0 or over 9 is considered out of bounds
bool Bug::wayIsBlocked() {
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

// Method that will increase the size of a winner bug depending on the sizes of the other bugs it has eaten
void Bug::grow(int growAmount) {
    this->size += growAmount;
}