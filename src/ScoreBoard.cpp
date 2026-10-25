#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(std::string name, int initialScore, int initialHealth) {
    this->playerName = name;
    this->baseScore = initialScore;
    this->currentScore = initialScore;
    this->penaltyPoints = 0;
    this->movesTracked = 0;
    this->healthTracked = initialHealth;
}

void ScoreBoard::syncWithPlayer(const Player& p) {
    this->movesTracked = p.getMovesCount();
    this->healthTracked = p.getHealth();
    // Each move costs 10 points; minimum score is 0
    int calculated = this->baseScore - (this->movesTracked * 10) - (this->penaltyPoints);
    this->currentScore = (calculated > 0) ? calculated : 0;
}

int ScoreBoard::getScore() const {
    return this->currentScore;
}

int ScoreBoard::getMoves() const {
    return this->movesTracked;
}

// Prefix ++ overload: increments moves and adjusts score
ScoreBoard& ScoreBoard::operator++() {
    this->movesTracked++;
    if (this->currentScore >= 10) {
        this->currentScore -= 10;
    }
    return *this;
}

// Binary - overload: returns a new ScoreBoard with penalty deducted
ScoreBoard ScoreBoard::operator-(int penalty) const {
    ScoreBoard temp = *this;

    if (penalty <= 0)
        return temp;

    temp.penaltyPoints += penalty;

    int calculated = temp.baseScore - (temp.movesTracked * 10) - temp.penaltyPoints;

    temp.currentScore = (calculated > 0) ? calculated : 0;

    return temp;
}

// Equality == overload
bool ScoreBoard::operator==(int targetMoves) const {
    return this->movesTracked == targetMoves;
}

// Friend function overloading << for clean HUD output
std::ostream& operator<<(std::ostream& os, const ScoreBoard& sb) {
    os << "+------------------------------------------+\n";
    os << "| PLAYER: " << sb.playerName 
       << " | HP: " << sb.healthTracked 
       << " | MOVES: " << sb.movesTracked 
       << " | SCORE: " << sb.currentScore << "\n";
    os << "+------------------------------------------+";
    return os;
}
