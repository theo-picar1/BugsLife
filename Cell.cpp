#include "Cell.h"
#include <iostream>

Cell::Cell()
{
    this->x = 0;
    this->y = 0;

    this->crawlers = {};
}

Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;

    this->crawlers = {};
};

int Cell::getX() const { return x; }

void Cell::setX(int x) { this->x = x; }

int Cell::getY() const { return y; }

void Cell::setY(int y) { this->y = y; }

list<Crawler *> Cell::getCrawlers() const { return crawlers; }

void Cell::setCrawlers(list<Crawler *> crawlers) { this->crawlers = crawlers; };

void Cell::addCrawler(Crawler *crawler)
{
    crawlers.push_back(crawler);
}

void Cell::displayCrawlers()
{
    if (this->crawlers.size() > 0)
    {
        for (auto &crawler : crawlers)
        {
            crawler->display();
        }
    }
    else
    {
        cout << "Empty" << endl;
    }
}

void Cell::clearCrawlers() {
    this->crawlers.clear();
}
