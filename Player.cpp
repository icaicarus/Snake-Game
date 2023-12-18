#include "Player.h"

Player::Player(GameMechs* thisGMRef) // Constructor
{
    // Intitializing data members
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList();

    // Initializing the head of the player as the first element of the array
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*'); 
    playerPosList->insertHead(tempPos);

}


Player::~Player() // Destructor
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() // Getter
{
    // Returns the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    /* PPA3 input processing logic:
        - Gets the input from the GameMechs ref
        - Enum direction is updated based on what iput what collected.
    */  
    char input = mainGameMechsRef->getInput();
    switch(input){
        case ' ':
            mainGameMechsRef->setExitTrue();
            break;
        case 'W':
        case 'w':
            if (myDir != DOWN)
            {
                myDir = UP;
            }
            break;
        case 'A':
        case 'a':
            if (myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;
        case 'S':
        case 's':
            if (myDir != UP)
            {
                myDir = DOWN;
            }
            break;

        case 'D':
        case 'd':
            if (myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }      
}

void Player::movePlayer()
{
    /* PPA3 Finite State Machine logic:
        - Gets the position of the player's head and iterates it around the board.
        - Direction is determined by the finite state enumeration set in updatePlayerPos()
    */
    
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    switch (myDir)
    {
        case UP:
            currentHead.y--;
            if(currentHead.y <= 0){
                currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;

        case RIGHT:
            currentHead.x++;
            if(currentHead.x > mainGameMechsRef->getBoardSizeX() - 2){
                currentHead.x = 1;
            }
            break;

        case LEFT:
            currentHead.x--;
            if(currentHead.x <= 0){
                currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;

        case DOWN:
            currentHead.y++;
            if(currentHead.y > mainGameMechsRef->getBoardSizeY() - 2){
                currentHead.y = 1;
            }
            break;

        default:
            break;
    }

    // Sets new player position after movements and deletes tail
    playerPosList->insertHead(currentHead);
    playerPosList->removeTail();
}

bool Player::checkSelfCollision()
{
    objPos head;
    objPos tempBody;
    playerPosList->getHeadElement(head);

    // Iterates through the player body array and compares each position to the position of the head
    for(int i = 2; i < playerPosList->getSize(); i++){
        playerPosList->getElement(tempBody, i);
        if(tempBody.isPosEqual(&head)){ 
            return true;
        }
    }
    return false;
}

