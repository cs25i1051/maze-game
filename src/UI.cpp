#include "UI.h"
#include <cctype>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

UI::UI(int rows, int cols) : gridRows(rows), gridCols(cols) {}

void UI::clearScreen() const {
    // ANSI escape sequence to clear screen and move cursor to top-left without flicker
    std::cout << "\033[2J\033[H";
}

void UI::renderWelcomeBanner() const {
    clearScreen();
    std::cout << "============================================\n";
    std::cout << "          TERMINAL MAZE RUNNER (OOP)        \n";
    std::cout << "============================================\n";
    std::cout << " Navigate 'P' to the Exit 'E' avoiding '#'. \n";
    std::cout << " Press any key to start...\n";
    getInstantInput();
}

void UI::renderControls() const {
    std::cout << "\n Controls: [W] Up  [A] Left  [S] Down  [D] Right  |  [Q] Quit\n";
}

// Overloaded << operator to render the current state of GameEngine
std::ostream& operator<<(std::ostream& os, const GameEngine& engine) {
    const maze& maze = engine.getMaze();
    const Player& player = engine.getPlayer();

    // Note: In GameEngine.cpp, r = p.getY() and c = p.getX()
    int playerRow = player.getY();
    int playerCol = player.getX();

    // Retrieve the actual maze dimensions for rendering
    int rows = maze.getRows();
    int cols = maze.getCols();

    os << "\n";
    for (int r = 0; r < rows; ++r) {
        os << "   ";
        for (int c = 0; c < cols; ++c) {
            if (r == playerRow && c == playerCol) {
                os << "P ";
            } else if (maze.isExit(r, c)) {
                os << "E ";
            } else if (maze.isWalkable(r, c)) {
                os << ". ";
            } else {
                os << "# ";
            }
        }
        os << "\n";
    }
    return os;
}

void UI::renderFrame(const GameEngine& engine, const ScoreBoard& sb) const {
    clearScreen();
    // Uses overloaded << for ScoreBoard
    std::cout << sb << "\n";
    // Uses overloaded << for GameEngine
    std::cout << engine;
    renderControls();
}

void UI::renderWinScreen(const ScoreBoard& sb) const {
    std::cout << "\n============================================\n";
    std::cout << "   CONGRATULATIONS! YOU ESCAPED THE MAZE!   \n";
    std::cout << "============================================\n";
    std::cout << sb << "\n";
    std::cout << " Final Score: " << sb.getScore() << " pts in " << sb.getMoves() << " moves!\n";
    std::cout << "============================================\n";
}

char UI::getInstantInput() const {
#ifdef _WIN32
    char ch = _getch();
    return std::toupper(static_cast<unsigned char>(ch));
#else
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable buffered I/O and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return std::toupper(static_cast<unsigned char>(ch));
#endif
}
