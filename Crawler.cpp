#include "Crawler.h"

Crawler::Crawler() { }

Crawler::Crawler(int id, Position position, int direction, int size, bool alive, list<Position> path) {
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

int Crawler::getDirection() const { return direction; }

void Crawler::setDirection(int direction) { this->direction = direction; }

int Crawler::getSize() const { return size; }

void Crawler::setSize(int size) { this->size = size; }

bool Crawler::isAlive() const { return alive; }

void Crawler::setAlive(bool alive) { this->alive = alive; }

std::list<Position> Crawler::getPath() const { return path; }

void Crawler::setPath(std::list<Position> path) { this->path = path; }