#include "Food.h"
#include <time.h>

Food::Food(GameMechs* gameMechs, objPosArrayList* playerPos){
    myGameMechs = gameMechs;
    foodPos.symbol = 'o';
    generateFood(playerPos);
}

Food::~Food()
{
}


void Food::generateFood(objPosArrayList* blockOff) {
    int foodX, foodY;
    bool valid;

    do {
        // Generate random food position within board boundaries
        foodX = rand() % ((myGameMechs->getBoardSizeX()) - 2) + 1;
        foodY = rand() % ((myGameMechs->getBoardSizeY()) - 2) + 1;

        valid = true; 
        for (int i = 0; i < blockOff->getSize(); i++) {
            objPos segment = blockOff->getElement(i);
            if (foodX == segment.pos->x && foodY == segment.pos->y) {
                valid = false; 
                break; 
            }
        }
    } while (!valid); 
    this->foodPos.setObjPos(foodX, foodY, foodPos.symbol);
}

objPos const Food::getFoodPos(){
    return foodPos;
}

bool Food::collisionCheck(objPosArrayList* playerPos){
    
    return playerPos -> getElement(0) == foodPos;
}


