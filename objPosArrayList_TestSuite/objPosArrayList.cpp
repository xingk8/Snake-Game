#include "objPosArrayList.h"
#include <cstddef>
#include <stdexcept>

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = 200;
    aList = new objPos[arrayCapacity];
    for(int i=0;i<arrayCapacity;i++){
        (*(aList+i) -> pos).x = 0;
        (*(aList+i) -> pos).y = 0;
        (aList+i) -> symbol = 0;
    }
    
}

objPosArrayList::objPosArrayList(const objPosArrayList &obj){
    listSize = obj.listSize;
    arrayCapacity = obj.arrayCapacity;
    aList = new objPos[arrayCapacity];
    for(int i=0;i<listSize;i++){
        *(aList +i) = obj.aList[i];
    }
}

objPosArrayList& objPosArrayList::operator=(const objPosArrayList &obj){
    if(this!=&obj){
        this -> listSize = obj.listSize;
        this -> arrayCapacity = obj.arrayCapacity;
        for(int i=0;i<listSize;i++){
        *((this -> aList) +i) = obj.aList[i];
    }
    }
    return *this;
}

void objPosArrayList::doubleSize(){
    arrayCapacity *= 2;
    objPos* temp = new objPos[arrayCapacity];
    for(int i=0;i<listSize;i++){
        *(temp+i) = *(aList+i);
    }
    delete[] aList;
    aList = temp;
}
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
    aList = NULL;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity){
        doubleSize();}

    for(int i=listSize;i>0;i--){
        *(aList+i) = *(aList + i -1);
    }
    *aList = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity){
        doubleSize();}
    *(aList + listSize) = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if(listSize==0){
        return;
    }
    for(int i=0;i<listSize;i++){
        *(aList+i) = *(aList+i+1);
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    if(listSize ==0){
        return;
    }
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return *(aList);
}

objPos objPosArrayList::getTailElement() const
{
    return *(aList +listSize - 1);
}

objPos objPosArrayList::getElement(int index) const
{
    if(index<0||index>=arrayCapacity){
        throw std::out_of_range("Index Out Of Range.");
    }
    return *(aList + index);
}