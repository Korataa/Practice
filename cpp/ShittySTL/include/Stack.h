#pragma once

#include <initializer_list>

template <class Type>
class Stack
{
public:
	Stack() 
	{
		arr = nullptr;
		size = 0;
	}
	Stack(std::initializer_list<Type> list)
	{
		size = list.size();
		arr = new Type[size];

		for (int i = 0; i < size; i++)
		{
			//copy array, this looks ugly af
			arr[i] = list.begin()[i];
		}
	}
	~Stack()
	{
		size = 0;
		delete arr;
	}

	void push(Type value)
	{
		//grow array by 1
		Type* temp = arr;
		arr = new Type[size+1];
		
		//copy array, we use size-1 because arr has one more element than 
		for (int i = 0; i < size; i++)
		{
			arr[i] = temp[i];
		}
		//reflect growth in array in size and then add the final value of the array
		size++;
		arr[size-1] = value;
	}

	//return last element of the "stack" and "pop" it off
	Type& pop()
	{
		Type* tempArr = arr;
		arr = new Type[size - 1];

		//make the size var reflect the new array size
		size--;
		for (int i = 0; i < size; i++)
		{
			arr[i] = tempArr[i];
		}
		//clear old array
		delete[] tempArr;

		return temp;
	}

	//return last element of array but dont pop it off
	Type& peek() const
	{
		return arr[size - 1];
	}
private:
	Type* arr;
	int size;
};