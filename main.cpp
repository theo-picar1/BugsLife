#include "board.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

void load(vector<Crawler *> &crawlers, const string &file_name, Board *board);
void parseLine(const string &line, Crawler &crawler);
void createFileHistory(Board *board);

int main()
{
    vector<Crawler *> crawlers;
    Board *board = new Board();
    string fname = "crawler-bugs.txt";

    load(crawlers, fname, board);

    board->initializeBoard(crawlers);

    cout << "Displaying all bugs:" << endl;
    board->displayAllBugs();

    cout << "\nDisplaying bug by id (101)" << endl;
    cout << board->findBugById(101)->getId() << endl;

    cout << "\nDisplaying bug path\n" << endl;

    board->displayLifeHistory();

    for (auto i = 0; i < 10; i++)
    {
        board->tapBugBoard();
    }

    board->displayLifeHistory();

    createFileHistory(board);

    for(auto &crawler : crawlers){
        Cell* cell = board->getCell(crawler->getPosition().x, crawler->getPosition().y);
        cell->addCrawler(crawler);
    }

    board->displayBoard();

    return 0;
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