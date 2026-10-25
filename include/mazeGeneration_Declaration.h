#pragma once
#include <vector>
using namespace std;
struct cell { //to store the position of cell.
    int x, y;
    bool operator== (const cell&) const; //overloading struct cell.
};
class maze{
    private:
        int mapSeed;
        int mapHeight;
        int mapWidth;
        int** mazeGrid;
        cell entryPoint;
        cell exitPoint;
        vector<cell> floodFillAlgo(cell, int**);
        
    public:
        maze(int =1, int= 1, int= 89675315); //userDefined constructor.
        ~maze(); //userDefined destructor.
        void mazeGenerate();
        int cellValue(int, int);
        int getRows() const;
        int getCols() const;
        bool isWalkable(int, int) const;
        bool isExit(int, int) const;
};
