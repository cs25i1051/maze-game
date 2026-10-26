#ifndef GAME_ENGINE
#define GAME_ENGINE
#include"mazeGeneration_Declaration.h"
#include"Player.h"

class GameEngine
{   private:
        maze m;                //Stores Maze object constructed from Maze class(Class Composition)
        Player p;              //Stores Player object constructed from Player class(Class Composition)
        bool won;              //Tells whether player reached exit successfully or not
    
    public:
        GameEngine(int rows = 9,int cols = 9,int seed = 10000000+ rand()%80000000, int startRow = 1, int startCol = 1, int health = 10, bool w = false);   
        //Parameterised Constructor defaulting its arguments

        ~GameEngine() = default;            //default Destructor provided by compiler(no function definition required)

        bool movePlayer(char direction);    //Checks if a move is valid and updates the player position accordingly
        bool hasWon() const;                //Checks whether player has reached exit, cannot modify the object which calls it

        //Both the below functions cannot modify the object which calls them, due to the trailing const keyword
        const maze& getMaze() const;        //Allows test driver to access maze for displaying, read only access
        const Player& getPlayer() const;    //Allows test driver to access player's position, read only access(as const return type)
};

#endif
