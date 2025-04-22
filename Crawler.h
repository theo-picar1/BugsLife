#ifndef CRAWLER_H
#define CRAWLER_H

#include "Bug.h"
#include <string>

using namespace std;

class Crawler : public Bug {

public:
    Crawler();
    Crawler(int id, Position position, Direction direction, int size, bool alive, int eatenBy);

    // The virtual method
    void move() override;
};



#endif //CRAWLER_H
