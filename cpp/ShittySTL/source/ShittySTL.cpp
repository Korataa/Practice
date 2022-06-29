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

//functions
template <typename Type>
void printVectorOfInts(Vector<Type> vector);

int main()
{
    Vector<int> vector = { 1, 6, 9, 45, 24, 89, 143 };
    std::cout << "before adding to vector:" << std::endl;
    printVectorOfInts(vector);

    int numOfElements = 50;
    for (int i = 0; i < numOfElements; i++)
    {
        vector.add(i);
    }

    std::cout << "\n\nafter adding to vector:" << std::endl;
    printVectorOfInts(vector);

    //remove 25 elements (all at index 2) from vector
    for (int i = 0; i < 25; i++)
    {
        vector.remove(2);
    }
    std::cout << "\n\nafter removing 25 elements from vector at index 2: " << std::endl;
    printVectorOfInts(vector);

    Vector<int> vector2 = { 87, 45, 32, 5, 78, 99, 1566 };
    //copy assignment here
    vector = vector2;

    std::cout << "\n\nthis is vector after copy assignment with vector2: " << std::endl;
    printVectorOfInts(vector);
}

template <typename Type>
void printVectorOfInts(Vector<Type> vector)
{
    std::cout << "[";
    for (int i = 0; i < vector.getSize(); i++)
    {
        //reached the end so dont print out last comma
        std::cout << vector[i] << ", ";
    }
    std::cout << "]" << std::endl;
}