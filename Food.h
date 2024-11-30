#pragma once
#include "objPos.h"
#include "GameMechs.h"

class Food{

    private:
        objPosArrayList foodBin;
        GameMechs* myGameMechs;
        char specialSymbol = '$';
        char normalSymbol = 'o';
    
    public:
        Food(GameMechs* gameMech, objPosArrayList* playerPos);
        ~Food();

        void generateFood(objPosArrayList* blockOff, int numFood = 3, int numSpecialFood = 1);
        bool collisionCheck(objPosArrayList* playerPos, bool& specialFoodEaten);
        objPosArrayList* getFoodBin();
};