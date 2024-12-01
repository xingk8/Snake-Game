#include "objPos.h"
#include <cstddef>


objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule


// Copy Constructor
objPos::objPos(const objPos& position){
    this -> symbol = position.symbol;
    this -> pos = new Pos;
    pos -> x = position.pos -> x; 
    pos -> y = position.pos -> y;
}   

// Copy Assignment Operator
objPos& objPos::operator=(const objPos &position){
    
    if(this != &position){
        this -> symbol = position.symbol;
        pos -> x = position.pos -> x; 
        pos -> y = position.pos -> y;}
    return *this; 
}

//set a defined definition for == when comparing objPos objects that compares the x and y values (not symbols) and returns a bool depending on if theyre the same or not
bool objPos::operator==(const objPos &other){
     return this->pos->x == other.pos->x &&
            this->pos->y == other.pos->y;
}

void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}

// Destructor 
objPos::~objPos(){
    delete(pos);
    pos = NULL;
}

