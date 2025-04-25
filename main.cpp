#include "Board.h"
#include "Crawler.h"
#include "SuperBug.h"
#include "Hopper.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Basic methods
void menu(Board *board = new Board());
void load(vector<Bug *> &bugs, const string &file_name);
void parseLine(const string &line, Bug* &bug);
void createFileHistory(Board *board);
void displayMenu();
int sfmlApplication();

using namespace std;
struct ball
{
    int x, y;
    int moveXBy = 1;
    int moveYBy = 1;
    int id ;
    int cellSize;
    sf::CircleShape shape;
    ball(int i, int cellSize)
    {
        shape.setRadius(10);
        shape.setFillColor(sf::Color::Blue);
        x = rand()%8;
        y = rand()%8;
        id = i;
        this->cellSize = cellSize;
    }
    void move()
    {
        x+= moveXBy;
        y+=moveYBy;

        if(x >=8||x == 0)
        {
            moveXBy *= -1;
        }
        if(y >= 8||y == 0)
        {
            moveYBy *= -1;
        }
        cout <<id <<":" << x << " " << y << endl;
    }

    void draw(sf::RenderWindow &window)
    {
        shape.setPosition(x * cellSize, y*cellSize);
        window.draw(shape);
    }
};

int main()
{
    vector<Bug *> bugs;
    Board *board = new Board();
    string fname = "bugs.txt";

    load(bugs, fname);            // Get all bugs from the file first
    board->initializeBoard(bugs); // Then initialise the board with the bugs

    cout << "***** BUGS LIFE SIMULATOR *****" << endl;

    menu(board);
}

void menu(Board *board)
{
    displayMenu();

    int choice;
    cin >> choice;

    // Repeat code inside until user chooses exit option
    while (choice != 8)
    {
        switch (choice)
        {
        case 1:
            cout << "Displaying all bugs..." << endl;
            board->displayAllBugs();
            break;

        case 2:
        {
            cout << "Please enter the id of the bug you wish to find:" << endl;
            int id;
            cin >> id;

            board->findBugById(id);

            break;
        }
        case 3:
            board->tapBugBoard();
            break;
        case 4:
            board->displayLifeHistory();
            break;
        case 5:
            board->displayBoard();
            break;
        case 6:
            cout << "Running simulation..." << endl;
            board->runSimulation();
            break;
        case 7:
            cout << "Runing SFML Application..." << endl;
            sfmlApplication();
        case 8:
            cout << "Ending simulation... Done! Goodbye." << endl;
            break;
        default:
            cout << "Invalid option. Please choose options 1-8!" << endl;
        }

        displayMenu();

        cin >> choice;
    }

    createFileHistory(board);
}

void createFileHistory(Board *board)
{

    // Create and open a text file
    ofstream MyFile("bugs_life_history_date_time.out.txt");

    // Write to the file
    MyFile << board->getLifeHistory();

    // Close the file
    MyFile.close();
}

void load(vector<Bug *> &bugs, const string &fname)
{
    ifstream fin(fname);

    // if file was not found either due to no file found or incorrect path
    if (!fin)
    {
        cout << "Error opening file: " << fname << endl;
        return;
    }

    string line;

    // keep going while there is still content in the file
    while (getline(fin, line))
    {
        string type;

        stringstream ss(line);

        // get type
        getline(ss, type, ',');

        Bug *bug = nullptr;

        if(type == "S"){
            bug = new SuperBug();
        }else if(type == "C"){
            bug = new Crawler();
        }

        parseLine(line, bug);

        // push back the bug into the vector
        bugs.push_back(bug);
    }

    fin.close();
}

// CSV file is as follows: type, id, x pos, y pos, direction, and size
void parseLine(const string &line, Bug* &bug)
{
    string type, id, x, y, size, direction;
    stringstream ss(line);

    // get type
    getline(ss, type, ',');

    // get id
    getline(ss, id, ',');

    // get up x and y position
    getline(ss, x, ',');

    getline(ss, y, ',');

    // get direction
    getline(ss, direction, ',');

    // get size
    getline(ss, size, ',');

    if (type == "C")
    {
        // make Crawler
        bug = new Crawler(stoi(id), Position(stoi(x), stoi(y)), static_cast<Direction>(stoi(direction)), stoi(size), true, -1);
    } else if (type == "S"){
        // make SuperBug
        bug = new SuperBug(stoi(id), Position(stoi(x), stoi(y)), static_cast<Direction>(stoi(direction)), stoi(size), true, -1);
    } else if (type == "H") { // make Hopper
        string hopLength;
        // get hopLength
        getline(ss,hopLength,',');
        bug = new Hopper(stoi(id), Position(stoi(x), stoi(y)), static_cast<Direction>(stoi(direction)), stoi(size), true, -1, stoi(hopLength));
    }
}

int sfmlApplication() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    //    sf::CircleShape shape(10.f);
    //    window.setFramerateLimit(40);
    //    shape.setPosition(195, 195);
    //    shape.setFillColor(sf::Color::Green);
    //    int moveXBy = 5;
    //    int moveYBy = 5;
    //    bool isGreen = true;
    vector<ball> balls;
    for(int i  = 0; i < 3; i++) {
        balls.push_back(ball(i, 50));
    }
    int size = 8;
    vector<sf::RectangleShape> board;
    bool blk = true;
    for(int x = 0; x < size; x++)
    {
        for(int y = 0; y < size; y++)
        {
            sf::RectangleShape rect(sf::Vector2f(50,50));
            rect.setPosition(x*50, y*50);
            if(blk)
            {
                rect.setFillColor(sf::Color::Black);

            }
            else
            {
                rect.setFillColor(sf::Color::White);
            }
            blk = !blk;
            board.push_back(rect);
        }
        blk = !blk;
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for(ball &b: balls) {
                        b.move();
                    }
                }

            }
            if(event.type == sf::Event::KeyReleased)
            {
                cout << event.key.code << endl;
                cout << sf::Keyboard::C << endl;
                if(event.key.code == sf::Keyboard::Up)
                {
                    for(ball &b: balls) {
                        b.move();
                    }
                }
            }
            //            if(event.type == sf::Event::MouseButtonReleased)
            //            {
            //                if(event.mouseButton.button == sf::Mouse::Left)
            //                {
            //                    if(isGreen)
            //                    {
            //                        shape.setFillColor(sf::Color::Red);
            //                        isGreen=false;
            //                    }
            //                    else
            //                    {
            //                        shape.setFillColor(sf::Color::Green);
            //                        isGreen=true;
            //                    }
            //                }
            //            }

        }
        //        shape.move(moveXBy, moveYBy);
        //        if(shape.getPosition().x >=380 ||shape.getPosition().x <5 )
        //        {
        //            moveXBy*=-1;
        //        }
        //        if(shape.getPosition().y >=380 ||shape.getPosition().y <10 )
        //        {
        //            moveYBy*=-1;
        //        }

        window.clear(sf::Color::White);
        for(sf::RectangleShape &rect : board)
        {
            window.draw(rect);
        }

        for(ball &b: balls) {

            b.draw(window);
        }
        window.display();

    }

    return 0;
}

void displayMenu()
{
    cout << "*************************************************" << endl
         << "Please choose one of the following options (1-8):" << endl
         << "1. Display all bugs" << endl
         << "2. Display bug by id" << endl
         << "3. Tap/Shake bug board" << endl
         << "4. Display bug life history" << endl
         << "5. Display board (All cells)" << endl
         << "6. Run simulation" << endl
         << "7. Run SFML Application" << endl
         << "8. Exit" << endl
         << "*************************************************" << endl;
}