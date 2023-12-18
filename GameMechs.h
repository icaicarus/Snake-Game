#ifndef GAMEMECHS_H
#define GAMEMECHS_H

// Required libraries for random food generation
#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        /*
        Private data members for contructing an instance of GameMechs
        Includes:   keyboard input, 
                    exit/loss conditions, 
                    display screen size,
                    food object,
                    player score
        */

        char input;
        bool exitFlag;
        int boardSizeX;
        int boardSizeY;
        bool loseFlag;
        int score; 
        objPos foodPos;

    public:
        // Constructors
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        // Destructor
        ~GameMechs();

        // Getters 
        int getBoardSizeX();
        int getBoardSizeY();
        char getInput();
        bool getExitFlagStatus();
        bool getLoseFlagStatus();
        int getScore(); 
        void getFoodPos(objPos &returnPos);
        
        // Game exit conditions
        void setLoseFlag();
        void setExitTrue();

        // Keyboard input processing
        void setInput(char this_input);
        void clearInput();

        // Player score keeping
        void incrementScore();

        // Food generation method
        void generateFood(objPosArrayList *blockOff); 
};

#endif