#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"
#include <chrono>

using namespace std;

#define DELAY_CONST 100000




void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player* player;
GameMechs* game;
Food* foodPos;



int main(void)
{

    Initialize();

    while(game->getExitFlagStatus() == false && game->getLoseFlagStatus() == false) // stop running when you lose or want to exit 
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}
// to calculate elasped time
std::chrono::time_point<std::chrono::steady_clock> startTime;

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    game = new GameMechs(30,15);
    player = new Player(game);
    foodPos = new Food(game, player -> getPlayerPos());
    

    startTime = std::chrono::steady_clock::now();
}

void GetInput(void)
{
   if(MacUILib_hasChar()){
        game->setInput(MacUILib_getChar());
        if(game->getInput()==' '){
            game -> setExitTrue();
    }
        
    }
    else{
        game -> setInput(0);
    }
}

void RunLogic(void)
{
    player -> updatePlayerDir();
    player -> movePlayer(foodPos);
}

void DrawScreen(void) {
    MacUILib_clearScreen();
    
    auto currentTime = std::chrono::steady_clock::now();
    int elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

    for (int y = 0; y < game->getBoardSizeY(); y++) {
        MacUILib_printf("                    ");
        for (int x = 0; x < game->getBoardSizeX(); x++) {

            if (x == 0 || x == game->getBoardSizeX() - 1 || y == 0 || y == game->getBoardSizeY() - 1) {
                MacUILib_printf("#");
            }   else {
                    bool isSnake = false;
                    for (int i = 0; i < player->getPlayerPos()->getSize(); i++) {
                        objPos segment = player->getPlayerPos()->getElement(i);
                        if (x == segment.pos->x && y == segment.pos->y) {
                            MacUILib_printf("%c", segment.symbol);
                            isSnake = true;
                            break;
                        }
                    }
                if (!isSnake) {
                    bool isFood = false;
                    for (int i = 0; i < foodPos->getFoodBin()->getSize(); i++){
                        objPos food = foodPos->getFoodBin()->getElement(i);
                        if (x == food.pos->x && y == food.pos->y){
                            MacUILib_printf("%c", food.symbol);
                            isFood = true;
                            break;
                        }
                    }
                    if (!isFood){
                        MacUILib_printf(" ");
                    }

                }   
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("===============================2SH4 Snake Game==============================\n");
    MacUILib_printf("----------Instructions----------       |    -----------Game Stats-----------\n");
    MacUILib_printf("Use the W, A, S, D keys to move        |    Score (Food Eaten): %d                       \n",game->getScore());
    MacUILib_printf("The snake can't collide with itself    |    Elasped Time: %d seconds        \n", elapsedSeconds);  
    MacUILib_printf("Press space to exit                    |    Food Positions:                 \n"); 

    for (int i = 0; i < foodPos->getFoodBin()->getSize(); i++){
        objPos food = foodPos->getFoodBin()->getElement(i);
        if(i==0){

    MacUILib_printf("Food $ gives 5 points                  |    Food %c at (%d,%d)\n", food.symbol, food.pos->x, food.pos->y);} 
        else if(i==1){   
    MacUILib_printf("Food o gives 1 point                   |    Food %c at (%d,%d)\n", food.symbol, food.pos->x, food.pos->y);}
    else{
    MacUILib_printf("Snake is * and wall is #               |    Food %c at (%d,%d)\n", food.symbol, food.pos->x, food.pos->y);
    }}
    MacUILib_printf("============================================================================="   );
    
}
 

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    // different outputs depending on whether you lost or exited 
    if(game->getExitFlagStatus() ==true){
        MacUILib_printf("-------------Thanks for Playing!------------\n");
        MacUILib_printf("Kun Xing                    Ibtisam Alhasoon\n");
        MacUILib_printf(
                    " __  __      __  __           _               \n"
                    "|  \\/  | ___|  \\/  | __ _ ___| |_ ___ _ __    \n"
                    "| |\\/| |/ __| |\\/| |/ _` / __| __/ _ \\ '__|   \n"
                    "| |  | | (__| |  | | (_| \\__ \\ ||  __/ |      \n"
                    "|_|  |_|\\___|_|  |_|\\__,_|___/\\__\\___|_|      \n"
                    "| | | |_ __ (_)_   _____ _ __ ___(_) |_ _   _ \n"
                    "| | | | '_ \\| \\ \\ / / _ \\ '__/ __| | __| | | |\n"
                    "| |_| | | | | |\\ V /  __/ |  \\__ \\ | |_| |_| |\n"
                    " \\___/|_| |_|_| \\_/ \\___|_|  |___/_|\\__|\\__, |\n"
        "                                        |___/  \n"
    );}
    else if(game -> getLoseFlagStatus() == true){
        MacUILib_printf("-------You Lost! Better Luck Next Time.-------\n");
        MacUILib_printf("Kun Xing                    Ibtisam Alhasoon\n");
        MacUILib_printf(
                    " __  __      __  __           _               \n"
                    "|  \\/  | ___|  \\/  | __ _ ___| |_ ___ _ __    \n"
                    "| |\\/| |/ __| |\\/| |/ _` / __| __/ _ \\ '__|   \n"
                    "| |  | | (__| |  | | (_| \\__ \\ ||  __/ |      \n"
                    "|_|  |_|\\___|_|  |_|\\__,_|___/\\__\\___|_|      \n"
                    "| | | |_ __ (_)_   _____ _ __ ___(_) |_ _   _ \n"
                    "| | | | '_ \\| \\ \\ / / _ \\ '__/ __| | __| | | |\n"
                    "| |_| | | | | |\\ V /  __/ |  \\__ \\ | |_| |_| |\n"
                    " \\___/|_| |_|_| \\_/ \\___|_|  |___/_|\\__|\\__, |\n"
        "                                        |___/  \n"
    );
    }
    MacUILib_printf("\n");
    MacUILib_printf("\n");
    MacUILib_printf("\n");
    MacUILib_printf("\n");

    MacUILib_uninit();
    delete(player);
    delete(game);
    delete(foodPos);
}
