#include <iostream>
#include<ctime>
#include "GameEngine.h"
#include "ScoreBoard.h"
#include "UI.h"

int main() {
    srand(time(0));
    const int ROWS = 9;
    const int COLS = 9;
    const int SEED = 10000000 + rand() % 80000000; //Since 8-Bit seed.
    const int START_ROW = 1;
    const int START_COL = 1;
    const int START_HEALTH = 10;

    // 1. Initialize Backend Engine, ScoreBoard, and Terminal UI
    GameEngine engine(ROWS, COLS, SEED, START_ROW, START_COL, START_HEALTH, false);
    ScoreBoard scoreboard("Player 1", 1000, START_HEALTH);
    UI terminalUI(ROWS, COLS);

    // 2. Display Welcome Screen
    terminalUI.renderWelcomeBanner();

    // 3. Main Game Loop
    bool isRunning = true;
    std::string statusMsg = "";

    while (isRunning && !engine.hasWon()) {
        scoreboard.syncWithPlayer(engine.getPlayer());
        terminalUI.renderFrame(engine, scoreboard);

        if (!statusMsg.empty()) {
            std::cout << " > " << statusMsg << "\n";
        }

        char input = terminalUI.getInstantInput();

        if (input == 'Q') {
            std::cout << "\n Exiting game. Goodbye!\n";
            isRunning = false;
            break;
        }

        if (input == 'W' || input == 'A' || input == 'S' || input == 'D') {
            bool moved = engine.movePlayer(input);
            if (moved) {
                statusMsg = "";
            } else {
                statusMsg = "Blocked by a wall (#)! Try another direction.";
                // Apply a small 5-point wall-bump penalty using overloaded - operator
                scoreboard = scoreboard - 5;
            }
        } else {
            statusMsg = "Invalid key! Use W, A, S, D to move or Q to quit.";
        }
    }

    // 4. Check Win Condition
    if (engine.hasWon()) {
        scoreboard.syncWithPlayer(engine.getPlayer());
        terminalUI.renderFrame(engine, scoreboard);
        terminalUI.renderWinScreen(scoreboard);
    }

    return 0;
}
