// ShittySTL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../include/Vector.h"
#include "../include/LinkedList.h"

struct vec3
{
    int x;
    int y;
    int z;
};

int main()
{
    LinkedList list;
    list.append(5);
    list.append(10);
    list.append(150);
    list.append(50);
    list.append(30);
    list.append(80);
    list.append(18);
    list.append(1);

    try {
        list.insertAt(7, 25);
    }
    catch (std::exception e)
    {
        std::cout << "Failed to insert into the list, index was probably out of bounds." << std::endl;
    }

    list.printList();

    std::cout << "Size of linked list is: " << list.getSize() << std::endl;
}