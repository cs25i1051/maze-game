#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include<string>

using namespace std;

struct Position{  //A structure for storing player as coordinate
    int x;
    int y;
};

class Player{
    private:
        Position pos;  
        int health;  //private data member for maintaing health of player
        int movesCount;  //for counting the number of moves of the player

    public:
        Player(int x,int y,int health);  //Parametrized constructor
        void setPosition(int x,int y); 
        void reduceHealth(int health);  //member function for reducing the health of player when it performs a wrong move
        void move(int deltaX,int deltaY);  //member fuction for changing the coordinates of player 

        int getX() const; //Returns the current column
        int getY() const; //Returns the current row
        int getHealth() const; //return the current health of player 
        int getMovesCount() const;  //return the current value of number of moves of player
};
#endif
