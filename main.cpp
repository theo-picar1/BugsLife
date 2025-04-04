#include "board.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

// Basic methods
void menu(vector<Crawler*> &crawlers, Board *board = new Board());
void load(vector<Crawler *> &crawlers, const string &file_name, Board *board);
void parseLine(const string &line, Crawler &crawler);
void createFileHistory(Board *board);

int main() {
    vector<Crawler*> crawlers;
    Board *board = new Board();
    string fname = "crawler-bugs.txt";

    load(crawlers, fname, board); // Get all crawlers from the file first
    board->initializeBoard(crawlers); // Then initialise the board with the crawlers
    board->updateCells(); // Then add the crawlers to their corresponding cells

    cout << "***** BUGS LIFE SIMULATOR *****" << endl;

    menu(crawlers, board);
}

void menu(vector<Crawler *> &crawlers, Board *board) {
    cout << "Please choose one of the following options (1-8):" << endl
         << "1. Display all bugs" << endl
         << "2. Display bug by id" << endl
         << "3. Tap/Shake bug board" << endl
         << "4. Display bug life history" << endl
         << "5. Display board (All cells)" << endl
         << "6. Run simulation" << endl
         << "7. Exit" << endl;

    int choice;
    cin >> choice;

    // Repeat code inside until user chooses exit option
    while (choice != 7) {
        switch (choice) {
            case 1:
                cout << "Displaying all bugs..." << endl;
                board->displayAllBugs();
                break;

            case 2: {
                int id;
                bool found = false;

                cout << "Please enter the id of the bug you wish to find:" << endl;
                cin >> id;

                for (auto crawler : crawlers) {
                    if (crawler->getId() == id) {
                        crawler->display();
                        found = true;
                    }
                }

                if (!found) {
                    cout << "No bug found with the id: " << id << endl;
                }
                
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
                cout << "Ending simulation... Done! Goodbye." << endl;
                break;
            default:
                cout << "Invalid option. Please choose options 1-8!" << endl;
        }

        cout << "\n1. Display all bugs" << endl
             << "2. Display bug by id" << endl
             << "3. Tap/Shake bug board" << endl
             << "4. Display bug life history" << endl
             << "5. Display board (All cells)" << endl
             << "6. Run simulation" << endl
             << "7. Exit" << endl;

        cin >> choice;
    }
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

void load(vector<Crawler *> &crawlers, const string &fname, Board *board)
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
        Crawler *crawler = new Crawler();
        parseLine(line, *crawler);
        // push back the crawler into the vector
        crawlers.push_back(crawler);
    }

    fin.close();
}

void parseLine(const string &line, Crawler &crawler)
{
    string id, x, y, size, direction, temp;
    Position position;
    stringstream ss(line);

    // skip over type of crawler for now
    getline(ss, temp, ',');

    // get id
    getline(ss, id, ',');

    // get up x and y position
    getline(ss, x, ',');

    getline(ss, y, ',');

    // get direction
    getline(ss, direction, ',');

    // get size
    getline(ss, size, ',');

    // make crawler
    crawler = Crawler(stoi(id), Position(stoi(x), stoi(y)), static_cast<Direction>(stoi(direction)), stoi(size), true, -1);
}