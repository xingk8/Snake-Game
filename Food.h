#pragma once
#include "objPos.h"
#include "GameMechs.h"

class Food{

    private:
        objPos foodPos;
        GameMechs* myGameMechs;
    
    public:
        Food(GameMechs* gameMech, objPosArrayList* playerPos);
        ~Food();

        void generateFood(objPosArrayList* blockOff);
        objPos const getFoodPos();
};