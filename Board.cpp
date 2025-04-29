#include "Board.h"
#include <iostream>
#include <list>
#include <set>

using namespace sf;

Board::Board() : bugs() {
}

Board::Board(const vector<Bug *> &bugs) {
    this->bugs = bugs;
}

// Occupy the 10x10 board with Bugs from bug_vector (assuming it is not empty)
void Board::initializeBoard(vector<Bug *> &bugs) {
    this->bugs = bugs;

    if (this->bugs.empty()) {
        cout << "There are no bugs to initialise the board with. Please create some bugs!" << endl;
    }

    // Creates a board (10x10 2d vector)
    board.resize(10, vector<Cell *>(10));

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Create a new cell with position i and j
            board[i][j] = new Cell(i, j);
        }
    }
}

// Display property of every bug on the board: Their id, type, position, status, etc
void Board::displayAllBugs() {
    for (auto &bug: bugs) {
        bug->display();
    }
}

// Method to find and display a with a given id
void Board::findBugById(int id) {
    for (auto &bug: bugs) {
        if (bug->getId() == id) {
            cout << "Bug found!" << endl;
            bug->display();
            return; // End the method since bug has already been found
        }
    }

    cout << "No bug found with an ID of " << id << ". Please try again!" << endl;
}

// Method that will cause all the bugs in the board to move by 1 cell
void Board::tapBugBoard() {
    vector<Bug*> aliveBugs; // Keep track of all alive bugs to avoid double isAlive check

    cout << "\nTAPPING THE BOARD...\n";
    for (auto &bug : bugs) {
        if (bug->isAlive()) {
            cout << "Bug " << bug->getId() << " is moving...\n";
            bug->move();
            aliveBugs.push_back(bug);
        }
    }

    cout << "NEW POSITIONS:\n";
    for (auto &bug : aliveBugs) { // Only show the positions of all the alive bugs
        bug->display();
    }

    updateCells();
}


// Method to display all the cells with any bugs on the board
void Board::displayBoard() {
    updateCells();

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << "Cell (" << i << ", " << j << "): ";
            board[i][j]->displayBugs(); // Display all the bugs in that cell if any
        }
        cout << endl;
    }
}

// Displays life history of every superbug. The path they took, who they were eaten by, their status and more...
void Board::displayLifeHistory() {
    for (auto &bug: bugs) {
        bug->display();

        cout << "Path: ";
        for (auto &position: bug->getPath()) {
            cout << "(" << position.x << ", " << position.y << "), ";
        }

        if (bug->isAlive()) {
            cout << "Alive" << endl;
        }
        else {
            cout << "Eaten by " << bug->getEatenBy() << endl;
        }
    }
}

// Similar to displayLifeHistory(). Only difference is we append it to a string and return that string.
string Board::getLifeHistory() {
    // All code logic here is just appending to 'str', where str is the content that will be written to the txt file
    string str = "";
    for (auto &bug: bugs) {
        str += bug->getDisplay();
        str += "Path: ";
        for (auto &position: bug->getPath()) {
            str += "(" + to_string(position.x) + ", " + to_string(position.y) + "), ";
        }

        if (bug->isAlive() == true) {
            str += "Alive";
        } else {
            str += "Eaten by " + to_string(bug->getEatenBy());
        }
        str += "\n\n";
    }
    return str;
}

// Method that will constantly tap, update and display the board until there is one bug left standing
void Board::runSimulation() {
    int leftAlive = 0;

    // Keep going as long as there are more than one bug alive
    while (leftAlive != 1) {
        tapBugBoard();

        // Reset the counter and then count again in for loop below
        leftAlive = 0;

        // Logic to count all the bugs that are still alive on the board
        for (auto &bug: bugs) {
            if (bug->isAlive()) {
                leftAlive++;
            }
        }

        if (leftAlive > 1) {
            cout << "There are currently " << leftAlive << " bugs left on the board!" << endl;
        }
    }

    // Print the winner, who is the only remaining alive bug
    for (auto &bug: bugs) {
        if (bug->isAlive()) {
            cout << "***** WINNER IS BUG " << bug->getId() << ", AND IS " << bug->getSize() <<
                    " POINTS LARGE! *****" << endl;
            cout << endl;
        }
    }
}

// Returns a pointer to the memory address of board[x][y].
Cell *Board::getCell(int x, int y) {
    return board[x][y];
}

void Board::updateCells() {
    // Clear bug lists from each cell to prevent stacking
    for (auto &bug: bugs) {
        int i = bug->getPosition().getX();
        int j = bug->getPosition().getY();

        board[i][j]->clearBugs();
    }


    int fightsOccured = 0; // Just for message purposes
    cout << "\nFIGHT LOG" << endl;

    // Adding bug to a cell and fighting logic occurs in below for loop
    for (auto &bug: bugs) {
        // Get the cell that is equal to the current bug's i and j position
        Cell *cell = getCell(bug->getPosition().x, bug->getPosition().y);

        // Then add that bug to the cell object, only if it is alive
        if (bug->isAlive()) {
            cell->addBug(bug);
        }
    }

    set<Cell*> processedCells;
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            Cell* cell = getCell(x, y);
            if (cell->getBugs().size() > 1 && processedCells.find(cell) == processedCells.end()) { // Only proceed if the cell hasn't been processes yet
                cout << "A FIGHT IS OCCURRING AT CELL (" << x << ", " << y << ")" << endl;
                cell->fightAndEat();
                processedCells.insert(cell);
                fightsOccured++;
            }
        }
    }

    if (fightsOccured <= 0) {
        cout << "No bugs have fought or eaten each other during this tap!" << endl;
    }
}

int Board::runMoveableSFMLApplication()
{
    RenderWindow window(VideoMode(600, 600), "BugsLife SFML Simulator");
    vector<RectangleShape> tiles;
    vector<Sprite> sfmlBugs; // Vector to keep track of every single bug that appears on the board. This is mainly for clearing the old positions

    Texture playerTexture;
    playerTexture.loadFromFile("player.jpg");
    Sprite superbug;
    superbug.setTexture(playerTexture);

    float cellSize = 60;
    Vector2u textureSize = playerTexture.getSize(); // To get the dimensions of the image being used so that we can scale it down to be 1 cell big
    superbug.setScale(cellSize / textureSize.x, cellSize / textureSize.y); // Because image is too big
    superbug.setPosition(1, 1); // Initial position (can be updated later for dragging)

    Texture crawlerTexture;
    Texture hopperTexture;
    Texture superbugTexture;
    crawlerTexture.loadFromFile("crawler.jpg");
    hopperTexture.loadFromFile("hopper.jpg");
    superbugTexture.loadFromFile("super-bug.jpg");

    // Loop through the bugs and create new sprites for each one to push into the sfmlSprites vector
    for (auto &bug : bugs) {
        Sprite sfmlBug; // sprite for the other bug types
        std::cout << "Bug type: " << bug->getType() << std::endl;

        // Assign texture based on the type of bug
        if (bug->getType() == "Crawler") {
            sfmlBug.setTexture(crawlerTexture);
            textureSize = crawlerTexture.getSize();
        } else if (bug->getType() == "Hopper") {
            sfmlBug.setTexture(hopperTexture);
            textureSize = hopperTexture.getSize();
        } else if (bug->getType() == "SuperBug") {
            sfmlBug.setTexture(superbugTexture);
            textureSize = superbugTexture.getSize();
        }


        if (bug->isAlive()) {
            sfmlBug.setScale(cellSize / textureSize.x, cellSize / textureSize.y); // set sze for this particular bug
            sfmlBug.setPosition(bug->getPosition().x * cellSize, bug->getPosition().y * cellSize); // Set position based on the bug's defined  position from the text file
            sfmlBugs.push_back(sfmlBug); //push to the vector
        }
    }

    bool isSelected = false; // Flag to track if the bug is selected
    int bug_x, bug_y; // Variables to store the bug's position offsets when being dragged

    bool brown = true;
    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            RectangleShape tile(Vector2f(60,60));
            tile.setPosition(x*60, y*60);
            if(brown)
            {
                tile.setFillColor(Color(139, 69, 19));

            }
            else
            {
                tile.setFillColor(Color(34, 139, 34));
            }
            brown = !brown;
            tiles.push_back(tile);
        }
        brown = !brown;
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) { window.close(); }

            if (event.type == Event::MouseButtonPressed) {
                // Check if the mouse click is on the bug
                if (event.mouseButton.x > superbug.getPosition().x &&
                    event.mouseButton.x < superbug.getPosition().x + 60
                    && event.mouseButton.y > superbug.getPosition().y &&
                    event.mouseButton.y < superbug.getPosition().y + 60) {
                    isSelected = true; // Mark the bug as selected
                    bug_x = event.mouseButton.x - superbug.getPosition().x;
                    bug_y = event.mouseButton.y - superbug.getPosition().y;
                }

                tapBugBoard(); // Simulate tapping the board when the user clicks the left click mouse click thing

                // Also relod the board to get rid of the old positions
                sfmlBugs.clear();

                for (auto &bug : bugs) {
                    Sprite sfmlBug;

                    // If-else statement for checking the type of the bug to match it with its corresponding image from the orange debug file
                    if (bug->getType() == "Crawler") {
                        sfmlBug.setTexture(crawlerTexture);
                        textureSize = crawlerTexture.getSize();
                    }
                    else if (bug->getType() == "Hopper") {
                        sfmlBug.setTexture(hopperTexture);
                        textureSize = hopperTexture.getSize();
                    }else if (bug->getType() == "SuperBug") {
                        sfmlBug.setTexture(superbugTexture);
                        textureSize = superbugTexture.getSize();
                    }

                    if (!bug->isAlive()) {
                        // Red hue for the dead bug instead of removing it from the SFML app
                        sfmlBug.setColor(Color(255, 0, 0, 255));
                    }

                    // Then for each bug, set its scale, position
                    sfmlBug.setScale(cellSize / textureSize.x, cellSize / textureSize.y);
                    sfmlBug.setPosition(bug->getPosition().x * cellSize, bug->getPosition().y * cellSize);
                    sfmlBugs.push_back(sfmlBug);

                }

                // And let sfml know the new positions of the bugs
                for (int i = 0; i < bugs.size(); ++i) {
                    sfmlBugs[i].setPosition(bugs[i]->getPosition().x * 60, bugs[i]->getPosition().y * 60);
                }
            }

            if (event.type == Event::MouseMoved) {
                // Checks if mouse is down when it's moving to allow dragging the bug
                if (isSelected) {
                    superbug.setPosition(Vector2f(event.mouseMove.x - bug_x, event.mouseMove.y - bug_y));
                }
            }

            if (event.type == Event::MouseButtonReleased) {
                // sets is selected to false when mouse is released
                if (isSelected) {
                    // snap bug to grid
                    int mx = (event.mouseButton.x / 60) * 60;
                    int my = (event.mouseButton.y / 60) * 60;
                    superbug.setPosition(Vector2f(mx, my)); // Set the bug's new position
                    isSelected = false; // Unselect the bug
                }
            }
            // checks if any key is pressed
            if (event.type == Event::KeyPressed) {
                // checks if up key is pressed
                if (event.key.code == Keyboard::Key::Up) {
                    if (superbug.getPosition().y >= 60) {
                        superbug.setPosition(superbug.getPosition().x, superbug.getPosition().y - 60); // moves bug up
                    }
                }
                // checks if down key is pressed
                if (event.key.code == Keyboard::Key::Down) {
                    if (superbug.getPosition().y <= 535) {
                        superbug.setPosition(superbug.getPosition().x, superbug.getPosition().y + 60); // moves bug down
                    }
                }
                // checks if left key is pressed
                if (event.key.code == Keyboard::Key::Left) {
                    if (superbug.getPosition().x >= 60) {
                        superbug.setPosition(superbug.getPosition().x - 60, superbug.getPosition().y); // moves bug left
                    }
                }
                // checks if right key is pressed
                if (event.key.code == Keyboard::Key::Right) {
                    if (superbug.getPosition().x <= 535) {
                        superbug.setPosition(superbug.getPosition().x + 60, superbug.getPosition().y); // moves bug right
                    }
                }
            }
        }

        window.clear(Color(34, 139, 34)); // sets window with darker grass green background

        // draw all tiles
        for (RectangleShape &rect : tiles) {
            window.draw(rect);
        }

        // Draw all bugs
        for (auto &bug : sfmlBugs) {
            window.draw(bug); // Draw each bug sprite
        }

        window.draw(superbug); // Draw the superbug (if needed)
        window.display(); // display all that's been drawn
    }

    return 0;
}