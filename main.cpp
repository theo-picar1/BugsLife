#include "board.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void load_data_from_file(vector<Crawler *> &Crawler_vector, const string &file_name);
void parseLine(const string &line, Crawler &crawler);

int main()
{
    vector<Crawler *> Crawler_vector;
    Board *board = new Board();
    load_data_from_file(Crawler_vector, "crawler-bugs.txt");
    board->initializeBoard(Crawler_vector);
}

void load_data_from_file(vector<Crawler *> &Crawler_vector, const string &file_name)
{
    string fname = "crawler-bugs.txt";
    ifstream fin(fname);

    // if file was not found either due to no file found or inccorect path
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
        Crawler_vector.push_back(crawler);
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