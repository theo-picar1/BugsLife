#include "board.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void load(vector<Crawler *> &crawlers, const string &file_name);
void parseLine(const string &line, Crawler &crawler);

int main()
{
    vector<Crawler *> crawlers;
    Board *board = new Board();
    string fname = "crawler-bugs.txt";

    load(crawlers, fname);
    board->initializeBoard(crawlers);

    cout << "Displaying all bugs:" << endl;
    board->displayAllBugs();

    cout << "\nDisplaying bug by id (101)" << endl;
    cout << board->findBugById(101)->getId() << endl;

    board->tapBugBoard();

    return 0;
}

void load(vector<Crawler *> &crawlers, const string &fname)
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
    string temp;
    Position position;
    Direction direction;
    stringstream ss(line);
    pair<int, int> pos(0,0);

    // skip over type of crawler for now
    getline(ss, temp, ',');

    // get id
    getline(ss, temp, ',');
    crawler.setId(stoi(temp));

    // set up position
    getline(ss, temp, ',');
    position.x = stoi(temp);

    getline(ss, temp, ',');
    position.y = stoi(temp);

    crawler.setPosition(position);

    // set up direction
    getline(ss, temp, ',');
    direction = static_cast<Direction>(stoi(temp));
    crawler.setDirection(direction);

    // get size
    getline(ss, temp, ',');
    crawler.setSize(stoi(temp));
}