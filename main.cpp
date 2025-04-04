#include "board.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

// Basic methods
void menu();
void load(vector<Crawler *> &crawlers, const string &file_name, Board *board);
void parseLine(const string &line, Crawler &crawler);
void createFileHistory(Board *board);

int main() {
    menu();
    // cout << "***** BUGS LIFE SIMULATOR *****" << endl;
    //
    // vector<Crawler *> crawlers;
    // Board *board = new Board();
    // string fname = "crawler-bugs.txt";
    //
    // load(crawlers, fname, board);
    //
    // board->initializeBoard(crawlers);
    //
    // cout << "Displaying all bugs:" << endl;
    // board->displayAllBugs();
    //
    // cout << "\nDisplaying bug by id (101)" << endl;
    // cout << board->findBugById(101)->getId() << endl;
    //
    // cout << "\nDisplaying bug path\n" << endl;
    //
    // board->displayLifeHistory();
    //
    // for (auto i = 0; i < 10; i++)
    // {
    //     board->tapBugBoard();
    // }
    //
    // board->displayLifeHistory();
    //
    // createFileHistory(board);
    //
    // for(auto i = 0; i < 5; i++){
    //     cout << "----------------------------" << endl;
    //
    //     // move all bugs
    //     board->tapBugBoard();
    //
    //     // add crawlers to cells
    //     for(auto &crawler : crawlers){
    //         // Get the cell that is equal to the current crawler's i and j position
    //         Cell* cell = board->getCell(crawler->getPosition().x, crawler->getPosition().y);
    //
    //         // Then add that crawler to the cell object
    //         cell->addCrawler(crawler);
    //     }
    //
    //     cout << "\n---------- Move " << i + 1 << " ----------\n" << endl;
    //     // display board (all cells)
    //     board->displayBoard();
    //
    //     // make board have no crawlers
    //     board->initializeBoard(crawlers);
    // }
    //
    // return 0;
}

void menu() {
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

    while (choice != 7) {
        switch (choice) {
            case 1:
                cout << "Display bugs" << endl;
            break;

            case 2:
                cout << "Display bug by id" << endl;
            break;

            case 3:
                cout << "Shake" << endl;
            break;

            case 4:
                cout << "Life history" << endl;
            break;

            case 5:
                cout << "Cells" << endl;
            break;

            case 6:
                cout << "Run simulation" << endl;
            break;

            case 7:
                cout << "Ending simulation..." << endl;
            break;

            default:
                cout << "Invalid option. Please choose options 1-8!" << endl;
            break;
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