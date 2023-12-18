#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    public:
        // Direction state
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};
    
        // Constructor
        Player(GameMechs* thisGMRef);

        // Destructor
        ~Player();

        // Getter
        objPosArrayList* getPlayerPos();

        // Game function methods
        void updatePlayerDir();
        void movePlayer();
        bool checkSelfCollision();

    private:
        /*
        Private data members for contructing an instance of GameMechs
        Includes:   Array list containing each "piece" of the snake,
                    Enumeration containing movement direction,
                    Reference to GameMechs for player-user interactions.
        */
        
        objPosArrayList *playerPosList; 
        enum Dir myDir;
        GameMechs* mainGameMechsRef;
};

#endif