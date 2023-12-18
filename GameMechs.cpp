#include "GameMechs.h"
#include "MacUILib.h"

using namespace std;

GameMechs::GameMechs() // Default constructor
{
    // Initializes function's members
    boardSizeX = 30; 
    boardSizeY = 15; 
    input = 0; 
    exitFlag = false;
    loseFlag = false; 
    score = 0; 

    // Sets food object to appear outside the screen
    foodPos.setObjPos(-1, -1, 'o'); 

}

GameMechs::GameMechs(int boardX, int boardY) // Specialized constructor
{
    // Boundary check to prevent errors
    if( boardX <= 0){
		boardX = 30; 
	}
	if (boardY <= 0){
		boardY = 15;
	}

    // Same initializing as default constructor
    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0; 
    input = 0; 
    exitFlag = false; 
    loseFlag = false; 
    foodPos.setObjPos(-1, -1, 'o'); 
    score = 0; 
}

GameMechs::~GameMechs()
{
    // Empty due to lack of heap data members
}

// 7 getter methods listed below
bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }

    return input;   
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::getFoodPos(objPos &returnFood)
{
    /*Getter method for obtaining the current position of the food.
    Return value is written into the returnPos via pass by reference*/
    returnFood.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}

void GameMechs::setInput(char this_input) // Setting detected keyboard input
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0; 
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::setExitTrue() // Forced exit condition
{
    exitFlag = true;
}

void GameMechs::setLoseFlag() // Game loss condition
{
    loseFlag = true;
}

void GameMechs::generateFood(objPosArrayList *blockOff) // Food generation
{
    srand(time(NULL));
    /* Randomly generate x and y coord (make sure not barder or blockOff pos)
    generating number betwwen 0 - (cols-2 = 18) */
    foodPos.x = (rand() % (boardSizeX - 2)) + 1;
    foodPos.y = (rand() % (boardSizeY - 2)) + 1; 
    
    /* Loop through each item in blockOff array.
    Exit when the generated food doesn't overlap with the player body.*/
    objPos tempPos;
    for(int i = 0; i < blockOff->getSize(); i++){
        blockOff->getElement(tempPos, i);
        while(foodPos.isPosEqual(&tempPos)){
            // Regenerate new coordinates for the food object
            foodPos.x = (rand() % (boardSizeX - 2)) + 1;
            foodPos.y = (rand() % (boardSizeX - 2)) + 1;
        }
    }
}