#include "Player.h"
#include "MacUILib.h"
#include <iostream>


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos = new objPosArrayList();
    objPos start1 = objPos(15,15,'*');
    playerPos -> insertTail(start1);

    // more actions to be included
}


Player::~Player()
{
    delete(playerPos);
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return this -> playerPos;

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    if(mainGameMechsRef -> getInput() != 0){
        switch(mainGameMechsRef -> getInput()){
        {                      
                case ' ':  
                    break;
                    mainGameMechsRef -> setExitTrue();
                case 'A':
                case 'a':
                    if(myDir == LEFT || myDir == RIGHT){
                        break;}
                    else{
                        myDir = LEFT;
                        break;
                }
                
                
            // Add more key processing here
                case 'W':
                case 'w':
                    if(myDir == UP || myDir == DOWN){
                        break;}
                    else{
                        myDir = UP;
                        break;
                }
                
            // Add more key processing here 
                case 'D':
                case 'd':
                    if(myDir == LEFT || myDir == RIGHT){
                        break;}
                    else{
                        myDir = RIGHT;
                        break;
                }
                
                case 'S':
                case 's':
                    if(myDir == UP || myDir== DOWN){
                        break;}
                    else{
                        myDir = DOWN;
                        break;
                }
                default:
                    break;
        }
        mainGameMechsRef -> setInput(0);
    }

}}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos newHead = playerPos -> getHeadElement();
    switch(myDir){
        case LEFT:
            newHead.pos -> x -=1;
            break;
        case UP:
            newHead.pos -> y -=1;
            break;
        case RIGHT:
            newHead.pos -> x +=1;
            break;
        case DOWN:
            newHead.pos -> y +=1;
            break;
        case STOP:
            break;
    }

    if(newHead.pos -> x<=0){
        newHead.pos -> x = mainGameMechsRef -> getBoardSizeX() -2;
    }
    else if(newHead.pos -> x>=mainGameMechsRef -> getBoardSizeX()-1){
        newHead.pos -> x = 1;
    }
    if(newHead.pos -> y<=0){
        newHead.pos -> y = mainGameMechsRef -> getBoardSizeY() -2;
    }
    else if(newHead.pos -> y>=mainGameMechsRef -> getBoardSizeY()-1){
        newHead.pos -> y = 1;
    }

    playerPos -> insertHead(newHead);
    playerPos -> removeTail();
    
    for (int i = 1; i < playerPos->getSize(); i++) { 
        if (playerPos -> getHeadElement() == playerPos->getElement(i)) {
            mainGameMechsRef->setExitTrue(); 
            mainGameMechsRef->setLoseFlag(); 
        }
    }

}

bool Player::checkFoodConsumption(Food* foodObj){
    return playerPos -> getElement(0) == foodObj->getFoodPos();
}

void Player::increasePlayerLength(Food* foodObj){
    objPos currentHead = playerPos -> getHeadElement();
    objPos newHead = currentHead;
    newHead.symbol = '*';
    playerPos->insertHead(newHead);
    mainGameMechsRef -> incrementScore();
    
}

// More methods to be added