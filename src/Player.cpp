
#include<iostream>
#include<string>
#include"Player.h"

using namespace std;

//parametrized Constructor
Player::Player(int x,int y , int health){  
    this->pos.x=x;  //using this pointer for directly accessing the private datamember of the object of the class to which respect function call has been hapened
    this->pos.y=y; 
    this->health=health;
    this->movesCount=0;
}

void Player::setPosition(int x,int y){
    this->pos.x=x;
    this->pos.y=y;
}

void Player::reduceHealth(int damage){
    this->health-=damage;
}

void Player::move(int deltaX,int deltaY){
    this->pos.x+=deltaX;
    this->pos.y+=deltaY;
    this->movesCount++;
}

int Player::getX() const{  //all get member functions have been declared const for ensuring that function will not modify any non static data members of the class 
    return this->pos.x;
}

int Player::getY() const{
    return this->pos.y;
}

int Player::getHealth() const{
    return this->health;
}

int Player::getMovesCount() const{
    return this->movesCount;
}
