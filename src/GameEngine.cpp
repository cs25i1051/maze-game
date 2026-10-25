#include"GameEngine.h"

GameEngine::GameEngine(int rows, int cols, int seed, int startRow, int startCol, int health, bool w): m(rows,cols,seed), p(startCol,startRow,health)
{   //Maze and Player objects are constructed before the GameEngine constructor body executes
    //Member initialiser(:) is used to construct Maze and Player objects, by calling their constructors

    won = w;  //Assigning w to won(private data member)

}

bool GameEngine::movePlayer(char direction){
    //Input char direction is W/A/S/D

    if(won)
        return false;  //Prevents further movement if player has already reached exit

    int r = p.getY();
    int c = p.getX();

    switch(direction)
    {
    case 'W':
        r--;    //W-->Move Up
        break;
    case 'S':
        r++;    //S-->Move Down   
        break;
    case 'A':
        c--;    //A-->Move Left
        break;
    case 'D':
        c++;    //D-->Move Right
        break;
    default:
        return false;  //Invalid Input
    }   
    
    if (!m.isWalkable(r,c))         //Checks whether the destination is inside the maze and is not a wall
        return false;
    
    //Updates the player's coordinates
    p.move(c - p.getX(),r - p.getY());

    if (m.isExit(r,c))             //Checks whether player has reached exit after this move and updates won accordingly
        won = true;

    return true;                  //return true if move is valid and player's position is updated

}

bool GameEngine::hasWon() const{
    return won;     
}

const maze& GameEngine::getMaze() const{
    return m;
}

const Player& GameEngine::getPlayer() const{
    return p;
}
