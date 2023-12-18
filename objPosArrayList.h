#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        /*
        Private data members for contructing an instance of objPosArrayList
        Includes:   array of objects,
                    size of object array,
                    size of array list.
        */
        objPos* aList;
        int sizeList;
        int sizeArray;

    public:
        // Constructor
        objPosArrayList();

        // Destructor
        ~objPosArrayList();

        // Getters
        int getSize();
        void getHeadElement(objPos &returnPos);
        void getTailElement(objPos &returnPos);
        void getElement(objPos &returnPos, int index);

        // Array list manipulation methods
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
};

#endif