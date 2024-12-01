#include "Food.h"
#include <time.h>

Food::Food(GameMechs* gameMechs, objPosArrayList* playerPos) : myGameMechs(gameMechs), foodBin(){
    generateFood(playerPos);
}

Food::~Food() {}


void Food::generateFood(objPosArrayList* blockOff, int numFood, int numSpecialFood) {
    foodBin = objPosArrayList(); // Clear previous food item
    int foodX, foodY;

    for (int i = 0; i < numFood; i++){
        bool valid;
        do {
            // Generate random food position within board boundaries
            foodX = rand() % ((myGameMechs->getBoardSizeX()) - 2) + 1;
            foodY = rand() % ((myGameMechs->getBoardSizeY()) - 2) + 1;

            valid = true; 
            for (int j = 0; j < blockOff->getSize(); j++) {
                objPos segment = blockOff->getElement(i);
                if (foodX == segment.pos->x && foodY == segment.pos->y) {
                    valid = false; 
                    break; 
                }
            }

            // Ensure no overlap with existing food items
            for (int j = 0; j < foodBin.getSize(); j++){
                objPos existingFood = foodBin.getElement(j);
                if (foodX == existingFood.pos->x && foodY == existingFood.pos->y){
                    valid = false;
                    break;
                }

            }

        } while (!valid); 

        char symbol = (i < numSpecialFood) ? specialSymbol : normalSymbol;
        objPos newFood(foodX, foodY, symbol);
        foodBin.insertTail(newFood);
    }
}

objPosArrayList* Food::getFoodBin(){
    return &foodBin;
}
// Check if collided with food (mentioned in manual but player uses this function instead)
bool Food::collisionCheck(objPosArrayList* playerPos, bool& specialFoodEaten){
    objPos snakeHead = playerPos->getHeadElement();
    for (int i = 0; i < foodBin.getSize(); i++){
        if (snakeHead == foodBin.getElement(i)){
            specialFoodEaten = (foodBin.getElement(i).getSymbol() == specialSymbol);
            foodBin.removeTail();
            return true;
        }
    }
    return false;
}


