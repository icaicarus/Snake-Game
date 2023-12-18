#include <iostream>

// All used class libraries 
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

// Global pointers to the instances of Player and GameMechs creates
GameMechs* myGM;
Player* myPlayer;

// Function prototypes
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{
    Initialize();
    while((myGM->getExitFlagStatus()) == false)  // Run program until exit conditions met
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }
    CleanUp();
}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    // Construct and store GameMechs and Player objects on the heap
    myGM = new GameMechs(26, 13); // Makes a board that's 26x13
    myPlayer = new Player(myGM);
    myGM->generateFood(myPlayer->getPlayerPos()); // Creates a food object at the start of the program
}

void GetInput(void)
{
    // Collects the input ASCII character into the corresponding field in the gameMechs object 
    myGM->getInput();
}

void RunLogic(void)
{
    // Initializing local variables
    objPos tempFood;
    objPos tempBody;
    objPos newInsert;
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    myGM->getFoodPos(tempFood);

    // Player movement constrols
    myPlayer->updatePlayerDir();  
    myPlayer->movePlayer(); 

    /* Food collection:
        - Gets the head of the player and compares its position to the food object's
        - If equal, increments the score and generates a food object on the board
        - Simulataneously inserts a new object at the start of the player array to increasing its length
    */
    playerBody->getHeadElement(tempBody);
    if(tempBody.isPosEqual(&tempFood))
    {
        myGM->incrementScore();
        newInsert.setObjPos(tempBody.x, tempBody.y, '*');
        playerBody->insertHead(newInsert);
        myGM->generateFood(playerBody);
    }

    /* Self collision detection:
        - Checks whether the player's head has collided with any other "piece" of its body
        - If it does, trigger the game loss condition
    */
    if(myPlayer->checkSelfCollision())
    {
        myGM->setLoseFlag();
    }

    // Clears the input field in gameMechanics to avoid double-processing the input
    myGM->clearInput();
}

void DrawScreen(void)
{
    // Clearing the screen each loop
    MacUILib_clearScreen(); 

    // Initializing local variables
    bool drawn;
    objPos tempBody;
    objPos tempFood;
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    myGM->getFoodPos(tempFood);

    MacUILib_printf("-------- Snake :) --------\n"); // Game header message

    /* Gameboard drawing routine:
    A nested for-loop iterates through rows and columns, checking the game element it's supposed to draw.
    It does this by getting the indexes of each object present on the board and displaying its associates symbol.
    */
    for(int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for(int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            drawn = false;
            
            /* Drawing the player:
                - Iterates through the array list of player objects
                - Displays the symbol associates with each object instance each time it occurs
                - Once it's drawn, sets the boolean "drawn" to true, breaking the loop to prevent overlaps
            */
            for(int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if(j == tempBody.x && i == tempBody.y)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }
            if(drawn) continue;

            // Drawing the board border
            if(i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }

            // Drawing the food object
            else if(j == tempFood.x && i == tempFood.y)
            {
                MacUILib_printf("%c", tempFood.symbol);
            }

            // Filling in the rest of the board with whitespaces
            else
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }

    // Welcome message and score display
    MacUILib_printf("Press WASD to start moving the snake.\nPress SPACE to exit the game.\nScore: %d\n\n", myGM->getScore()); 

    // Forced-quit message
    if(myGM->getExitFlagStatus())
    {
        MacUILib_printf("Game quit."); 
    }

    // Game loss message         
    if(myGM->getLoseFlagStatus())
    {
        MacUILib_printf("Better luck next time!"); 
        myGM->setExitTrue();
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{ 
    MacUILib_uninit();

    // Deleting all heap data to avoid memory leaks
    delete myGM; 
    delete myPlayer;

}
