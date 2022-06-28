#pragma once

#include <initializer_list>
#include <algorithm>

template <class Type>
class Vector
{
public:
	Vector() 
	{ 
		size = 0;
		arr = nullptr;
	};

	Vector(std::initializer_list<Type> list)
	{
		size = list.size();
		arr = new Type[size];

		for (int i = 0; i < size; i++)
		{
			arr[i] = list.begin()[i];
		}
	}

	~Vector()
	{
		delete[] arr;
	}

	//adds an element to the end of the array
	void add(Type element)
	{
		size_t currentSize = size;
		Type* temp = new Type[currentSize + 1];
		for (int i = 0; i < currentSize; i++)
		{
			temp[i] = arr[i];
			if (i == currentSize - 1)
			{
				//we are at the end of the array so now we add element
				temp[i + 1] = element;
			}
		}
		//update size
		size++;

		//handle memory and pointer shit
		delete[] arr;
		arr = temp;
		temp = nullptr;
	}

	//removes the element at the specified index then shifts the rest of the array left
	void remove(int index)
	{
		size_t currentSize = size;
		Type* temp = new Type[currentSize - 1];

		int i = 0, j = 0; //we declare 2 ints here for indexes to make it easier to shift the array
		while (i < currentSize)
		{
			if (i == index)
			{
				//"Shift" over whole array and remove the element
				i++;
			}
			temp[j] = arr[i];
			i++;
			j++;
		}

		delete[] arr;
		arr = temp;
		temp = nullptr;
	}

	const int getSize()
	{
		return size;
	}

	Type& operator[] (int index)
	{
		return arr[index];
	}

	Type& get(int index)
	{
		return arr[index];
	}


private:
	Type* arr;
	size_t size;
};
