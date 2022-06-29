#pragma once

#include <initializer_list>
#include <algorithm>

//growth factor is 1.5 because i think 2 would cause the end of the array to be way too far away occasionally
const double GROWTH_FACTOR = 1.5;

template <class Type>
class Vector
{
public:
	//Constructors
	Vector() 
	{ 
		size = 0;
		capacity = 0;
		arr = nullptr;
	};
	Vector(std::initializer_list<Type> list) : 
		arr{ new Type[static_cast<size_t>(list.size() * GROWTH_FACTOR)] },
		size { list.size() }, 
		capacity{ static_cast<size_t>(list.size() * GROWTH_FACTOR) }
	{
		for (int i = 0; i < size; i++)
		{
			arr[i] = list.begin()[i];
		}
	}

	//Destructor
	~Vector()
	{
		delete[] arr;
	}

	//Copy constructor
	Vector(const Vector<Type>& oldVector)
		: arr{ new Type[oldVector.capacity] }, size{oldVector.size}, capacity{oldVector.capacity}
	{
		for (int i = 0; i < size; i++)
		{
			arr[i] = oldVector.arr[i];
		}
	}

	//copy assignment operator
	Vector<Type>& operator=(const Vector<Type>& oldVector)
	{
		if (this == &oldVector)
		{
			return *this;
		}
		delete[] this->arr;

		Type* tempArray = new Type[oldVector.capacity];
		for (int i = 0; i < oldVector.size; i++)
			tempArray[i] = oldVector.arr[i];

		this->arr = tempArray;
		this->size = oldVector.size;
		this->capacity = oldVector.capacity;
		tempArray = nullptr;
		return *this;
	}

	//adds an element to the end of the array
	void add(Type value)
  	{
		//check if array is full yet
		if (isFull())
		{
			growArray();
		}

		//add new value to behind all the other elements then update size
		size_t arrayEnd = size;		//size - 1 is the last element that has already been assigned because arrays are 0-indexed, a lot of my loops end at size - 1
		arr[arrayEnd] = value;
		size++;
	}

	//removes the element at the specified index then shifts the rest of the array left
	void remove(int index)
	{
		//temp possibly contains way too many elements but whatever
		Type* temp = new Type[capacity];

		int i = 0, j = 0; //we declare 2 ints here for indexes to make it easier to shift the array
		while (i < size)
		{
			if (i == index)
			{
				//"Shift" over whole array and remove the element by not copying it to new array
				i++;
			}
			temp[j] = arr[i];
			i++;
			j++;
		}
		//reflect new size of array
		size--;

		//delete old array and then make arr point to new array with one less element
		delete[] arr;
		arr = temp;
		temp = nullptr;

		std::cout << "\nRemoved element from array at index: " << index << std::endl;
	}

	const size_t getSize()
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
	size_t capacity;

	bool isFull()
	{
		return size == capacity;
	}

	void growArray()
	{
		capacity = static_cast<size_t>(GROWTH_FACTOR * size);

		if (size >= capacity)
		{
			std::cout << "size cant be smaller than capacity" << std::endl;
			return;
		}
		else 
		{
			Type* temp = new Type[capacity];
			for (int i = 0; i < size; i++)
			{
				std::cout << "copying array in growArray: " << arr[i] << std::endl;
				temp[i] = arr[i];
			}

			//delete old array and then make arr point to new array
			delete[] arr;
			arr = temp;
			temp = nullptr;

			std::cout << "grew the array!" << std::endl;
		}
	}
};
