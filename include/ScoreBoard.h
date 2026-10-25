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
    // Parameterized Constructor with default values
    ScoreBoard(std::string name = "Player 1", int initialScore = 1000, int initialHealth = 10);

    // Destructor
    ~ScoreBoard() = default;

    // Sync stats from the Player object
    void syncWithPlayer(const Player& p);

    // Getters
    int getScore() const;
    int getMoves() const;

    // OPERATOR OVERLOADING (Unary Prefix ++): Increment move counter & recalculate score
    ScoreBoard& operator++();

    // OPERATOR OVERLOADING (Binary -): Deduct penalty points from the scoreboard
    ScoreBoard operator-(int penalty) const;

    // OPERATOR OVERLOADING (Comparison ==): Check if moves match a specific count
    bool operator==(int targetMoves) const;

    // FRIEND FUNCTION + OPERATOR OVERLOADING (<<): Print HUD directly via std::cout << scoreboard
    friend std::ostream& operator<<(std::ostream& os, const ScoreBoard& sb);
};

#endif
