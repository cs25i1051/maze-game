#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <iostream>
#include <string>
#include "Player.h"

class ScoreBoard {
private:
    int currentScore;
    int baseScore;
    int penaltyPoints;
    int movesTracked;
    int healthTracked;
    std::string playerName;

public:
    //parameterized Constructor with default values
    ScoreBoard(std::string name = "Player 1", int initialScore = 1000, int initialHealth = 10);

    //destructor
    ~ScoreBoard() = default;

    //sync stats from the Player object
    void syncWithPlayer(const Player& p);

    // Getters
    int getScore() const;
    int getMoves() const;

    // increment move counter & recalculate score
    ScoreBoard& operator++();

    // deduct penalty points from the scoreboard
    ScoreBoard operator-(int penalty) const;

    //check if moves match a specific count
    bool operator==(int targetMoves) const;

    //print directly
    friend std::ostream& operator<<(std::ostream& os, const ScoreBoard& sb);
};

#endif
