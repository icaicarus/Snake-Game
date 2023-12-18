#include "objPosArrayList.h"

using namespace std;

objPosArrayList::objPosArrayList() // Default constructor
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList() // Destructor
{
    delete[] aList;
}

// 4 Getter methods listed below:
int objPosArrayList::getSize() 
{
    return sizeList;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if(sizeList == 0)
    {
        return;
    }
    
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if(sizeList == 0)
    {
        return;
    }
    returnPos.setObjPos(aList[sizeList-1]);
    
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if(sizeList == 0 || index < 0 || index >= sizeList)
    {
        return;
    }

    returnPos.setObjPos(aList[index]);
}


void objPosArrayList::insertHead(objPos thisPos)
{
    // Checking if the array is at max capacity
    if(sizeList == sizeArray)
    {
        return;
    }

    // Creating space for a new element to be inserted at index 0
    for(int i = sizeList; i > 0; i--){
        aList[i].setObjPos(aList[i - 1]);  // Shifting towards the tail
    }
    aList[0].setObjPos(thisPos);
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // Checking if the array is at max capacity
    if(sizeList == sizeArray)
    {
        return;
    }

    // Inserting an element at the end of the list
    aList[sizeList++].setObjPos(thisPos); 
}

void objPosArrayList::removeHead()
{
    // Checking if the array is empty
    if(sizeList == 0)
    {
        return;
    }

    for(int i = 0; i < sizeList - 1; i++)   
        aList[i].setObjPos(aList[i + 1]);  // Shifting towards the head

    sizeList--;
}

void objPosArrayList::removeTail()
{
    // Checking if the array is empty
    if(sizeList == 0)
    {
        return;
    }

    sizeList--;  
}

