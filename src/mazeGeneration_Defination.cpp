#include<iostream>
#include<cstdlib>
#include <unordered_map> //equivalent to dictionary.
#include<vector>
#include<queue>
#include<limits>
#include "../include/mazeGeneration_Declaration.h"
using namespace std;

maze:: maze(int height, int width, int seed){ //UserDefined constructor.
    //Checking if map's valid.
    if(height >= 3 && width >= 4){      //Minimum dimensions required for maze generation
        mapHeight= height;
        mapWidth = width;
        mazeGrid = new int*[mapHeight]; //i.e. stores each rows, i.e. each element of mapHeight.
        for(int x=0; x<mapHeight; x++){
            mazeGrid[x]= new int[mapWidth];
        }

        //Initializing every Block/Cell as walkable.(i.e. 0).
        for(int x=0; x< mapHeight; x++){
            for(int y=0; y< mapWidth; y++){
                mazeGrid[x][y]=0;
            }
        }
    }else{
        cout<<"Invalid maze dimensions! Minimum size is 3 rows and 4 columns."<< endl;
        abort();
    }

    //checking if seed valid, i.e. 8-bit seed.
    if(seed>=10000000 && seed<=99999999){
        mapSeed = seed;
        srand(seed); //Using an pseudo- random number generator.
    }else{
        cout<<"Invalid seed input! This Program is using 8-Bit int seed."<< endl;
        abort();
    }
    mazeGenerate();
}

maze::~maze(){ //UserDefined destructor.
    for(int x=0; x<mapHeight; x++){
        delete[] mazeGrid[x];
    }
    delete[] mazeGrid;
}

vector<cell> maze:: floodFillAlgo(cell initialStart, int** mazeGrid){
    vector<cell> tileList; //contains all cell of that particular region.
    queue<cell> tileQueue; //contains the tile array to be flooded. (FIFO).
    bool** visitedCell = new bool*[mapHeight]; //return whether the cell was already covered or not.
    for(int x=0; x< mapHeight; x++){
        visitedCell[x]= new bool[mapWidth];
    }

    //Initializing all visited to false.
    for(int x=0; x< mapHeight; x++){
        for(int y=0; y< mapWidth; y++){
            visitedCell[x][y]=false;
        }
    }

    tileQueue.push(initialStart); //starting the flood from intialStart cell.
    visitedCell[initialStart.x][initialStart.y] = true; //i.e. it is visited.

    while(!tileQueue.empty()){ //until there is tile leading/ flooding to another walkable path.
        cell currCell = tileQueue.front();
        tileList.push_back(currCell);
        tileQueue.pop();

        //Now visiting all up, down, left and right cell.
        if(currCell.x +1< mapHeight && mazeGrid[currCell.x+1][currCell.y]==0){// i.e. downCell exist and isWalkable.
            if(!visitedCell[currCell.x+1][currCell.y]){ //If not yet visited.
                visitedCell[currCell.x+1][currCell.y]= true; //then mark it visited.
                cell neighbourCell = {currCell.x+1, currCell.y};
                tileQueue.push(neighbourCell);
            }
        }
        if(currCell.x -1> 0 && mazeGrid[currCell.x-1][currCell.y]==0){// i.e. upCell exist.
            if(!visitedCell[currCell.x-1][currCell.y]){ //If not yet visited.
                visitedCell[currCell.x-1][currCell.y]= true; //then mark it visited.
                cell neighbourCell = {currCell.x-1, currCell.y};
                tileQueue.push(neighbourCell);
            }
        }
        if(currCell.y -1>0 && mazeGrid[currCell.x][currCell.y-1]==0){// i.e. leftCell exist.
            if(!visitedCell[currCell.x][currCell.y-1]){ //If not yet visited.
                visitedCell[currCell.x][currCell.y-1]= true; //then mark it visited.
                cell neighbourCell = {currCell.x, currCell.y-1};
                tileQueue.push(neighbourCell);
            }
        }
        if(currCell.y +1< mapWidth && mazeGrid[currCell.x][currCell.y+1]==0){// i.e. rightCell exist.
            if(!visitedCell[currCell.x][currCell.y+1]){ //If not yet visited.
                visitedCell[currCell.x][currCell.y+1]= true; //then mark it visited.
                cell neighbourCell = {currCell.x, currCell.y+1};
                tileQueue.push(neighbourCell);
            }
        }
    }

    //Deallocating the memory used.
    for(int x=0; x< mapHeight; x++){
        delete[] visitedCell[x];
    }
    delete[] visitedCell;

    return tileList; //returning the list.
}

int maze::getRows() const {
    // Returns the number of rows in the maze
    return mapHeight;
}

int maze::getCols() const {
    // Returns the number of columns in the maze
    return mapWidth;
}

void maze:: mazeGenerate(){
    //First Generating the boundary. (i.e. assiging border as 1).
    for (int y=0; y< mapWidth; y++) {
        mazeGrid[0][y] = 1; //i.e. wall.
        mazeGrid[mapHeight-1][y] = 1;
    }
    for (int x=0; x< mapHeight; x++) {
        mazeGrid[x][0] = 1; //i.e. wall.
        mazeGrid[x][mapWidth-1] = 1;
    }

    //Now Choosing two random opening for Start and Goal.
    int startIndex= 1+ rand()% (mapWidth-3);
    int endIndex = 1+ rand()% (mapWidth-3);

    //updating the starting and ending point in class.
    entryPoint= {0, startIndex};
    exitPoint ={mapHeight-1, endIndex};


    //Now, carving out the opening.
    for (int y = 0; y < mapWidth; y++) {
        if (startIndex == y || startIndex+1 == y) {
            mazeGrid[0][y] = 0; //i.e. walkable.
        };
        if (endIndex == y || endIndex +1 == y) {
            mazeGrid[mapHeight-1][y] = 0; //i.e. walkable.
        }
    }

    //Now adding random blockage for maze like pattern.
    //We are leaving one pixel are final boundary.
    for (int y = 1; y < mapWidth - 1; y++) { //Foreach column pixel.
        for (int x = 1; x < mapHeight - 1; x++) {
            float random = (float)(rand()%10)/10; //any pseduo random number between 0.0 to 1.0.
            int oppositeTile = 0;
            if (mazeGrid[x][y] == 1) oppositeTile = 0;
            else if (mazeGrid[x][y] == 0) oppositeTile = 1;
            mazeGrid[x][y] = random < 0.4f ? oppositeTile : mazeGrid[x][y];
            //i.e., every tile has 40% possibility to converting to its opposite tile, i.e. 1->0 and vise-versa Or continue with prev one.
        }
    }

    //Now cleaning up the all surrounding cell with possite cell.
    for (int x = 0; x < mapHeight; x++) {
        for (int y = 0; y < mapWidth; y++) {
            int gridValue = mazeGrid[x][y];
            if (y - 1 >= 0) { //If left cell exist.
                if (mazeGrid[x][y - 1] == gridValue) continue;
            }
            if (y + 1 < mapWidth) { //If right pixel exist.
                if (mazeGrid[x][y + 1] == gridValue) continue;
            }
            if (x - 1 >= 0) { //If Up pixel exist.
                if (mazeGrid[x - 1][y] == gridValue) continue;
            }
            if (x + 1 < mapHeight) { //If down pixel exist.
                if (mazeGrid[x + 1][y] == gridValue) continue;
            }

            //Change the value to its opposite.(i.e. if all surrounding are blockage tile, then tile convert to blockage, if its walkable).
            if (gridValue == 1) mazeGrid[x][y] = 0;
            else if (gridValue == 0) mazeGrid[x][y] = 1;
        }
    }
    
    //Ensure the player's default starting position (1,1) is walkable
    mazeGrid[1][1] = 0;

    //Now using flood-fill algorithm to create region and interconnect them so there exist atleast one path for each walkable tile from start.
    //Creating an region array to store region of each cell.
    int** regionArray = new int*[mapHeight];
    for(int x=0; x<mapHeight; x++){
        regionArray[x]= new int[mapWidth];
    }

    //Now assigning each region initial -1, representing no region assigned for each tile.
    for(int x=0; x< mapHeight; x++){
        for(int y=0; y< mapWidth; y++){
            regionArray[x][y]= -1;
        }
    }

    //Using an Dictionary to store each region and all its cell, to find minimum distance (Manhattan Dist).
    unordered_map<int, vector<cell>> regionTiles;

    //Now applying the flood-fill to allocate region.
    int currRegion=0;
    for(int x=0; x< mapHeight; x++){
        for(int y=0; y< mapWidth; y++){
            if(mazeGrid[x][y]==1) continue;
            if(regionArray[x][y]!=-1) continue; //since that cell is already assigned region.
            cell currCell = {x,y};
            vector<cell> allTile = floodFillAlgo(currCell, mazeGrid);
            regionTiles[currRegion] = allTile;
            int tileCount = allTile.size(); //total cell in that region.

            for(int i=0; i< tileCount; i++){ //foreach cell in that region.
                cell currCell = allTile[i];
                regionArray[currCell.x][currCell.y]= currRegion;
            }
            currRegion++; //incrementing/ changing region index.
        }
    }

    //Now finding the shortest path to carve between two regions.
    //Here, currRegion has now become an total region count.
    for(int i=0; i< currRegion-1; i++){ //connecting two alternate region.
        cell regionA_point= {0,0};
        cell regionB_point= {0,0};

        //now finding minimum manhantan distance between every two point, brute force.
        int minDistance = numeric_limits<int>::max(); 
        //storing max in min, so it takes first value is always smaller than min.

        int regionACount = regionTiles[i].size();
        int regionBCount = regionTiles[i+1].size();

        for(int j=0; j< regionACount; j++){
            for(int k=0; k< regionBCount; k++){
                //calculating Manhattan Distance.
                int dist= abs(regionTiles[i][j].x - regionTiles[i+1][k].x) + abs(regionTiles[i][j].y - regionTiles[i+1][k].y);
                if (minDistance > dist) {
                    minDistance = dist;
                    regionA_point = regionTiles[i][j];
                    regionB_point = regionTiles[i+1][k];
                }
            }
        }

        //Now carving the smallest path.
        int x = regionA_point.x;
        int y = regionA_point.y;
        //move throughout x.
        while (x != regionB_point.x) {
            if (x > regionB_point.x) {
                x--;
                mazeGrid[x][y] = 0;
            } else {
                x++;
                mazeGrid[x][y] = 0;
            }
        }

        //move throughtout y.
        while (y != regionB_point.y) {
            if (y > regionB_point.y) {
                y--;
                mazeGrid[x][y] = 0;
            } else {
                y++;
                mazeGrid[x][y] = 0;
            }
        }
    }

    //deleting the region Array since our work of connecting isolated walkable path is done.
     for(int x=0; x<mapHeight; x++){
        delete[] regionArray[x];
    }
    delete[] regionArray;
}

bool maze:: isWalkable(int row, int column) const{
    //validating if valid value.
    if(row>=0 && row< mapHeight && column>=0 && column< mapWidth){
        if(mazeGrid[row][column]==0) return true;
        else return false;
    }
    else{
        cout<<"Invalid row and column value"<< endl;
    }
    return false;
}

bool maze:: isExit(int row, int column) const{
    //validating if valid value.
    if(row>=0 && row< mapHeight && column>=0 && column< mapWidth){
        cell currCellA = {row, column};
        cell currCellB = {row, column-1};
        if(currCellA== exitPoint) return true;
        else if(currCellB== exitPoint) return true;
        else return false;
    }
    else{
        cout<<"Invalid row and column value"<< endl;
    }
    return false;
}

bool cell:: operator==(const cell &other) const{
    if(other.x == this->x){
        if(other.y== this->y){
            return true;
        }
    }
    return false;
}

int maze::cellValue(int row, int column){
    //validating if valid value.
    if(row>=0 && row< mapHeight && column>=0 && column< mapWidth){
        return mazeGrid[row][column];
    }
    else{
        cout<<"Invalid row and column value"<< endl;
    }
    return -1;
}

/*
Assumption:
    In grid, 1 means blockage/ wall and 0 means walkable.

*/
