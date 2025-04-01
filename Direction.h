//
// Created by Theo Picar on 01/04/2025.
//

#ifndef DIRECTION_H
#define DIRECTION_H

// 'enum class' instead of just 'enum' to prevent variables from being global
// Will be called as Direction::North rather than just NORTH
enum class Direction {
    NORTH = 1,
    WEST = 2,
    SOUTH = 3,
    EAST = 4
};

#endif //DIRECTION_H
