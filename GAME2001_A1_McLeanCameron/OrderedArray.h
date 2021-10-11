#pragma once
#include <cassert>
#include "Array.h"
#include <cstring>

template<class T>

class OrderedArray:public Array<T>
{
public:
	// Constructor
	OrderedArray(int size, int growBy = 1)
	{
		if (size)	
		{
			Array<T>::m_maxSize = size;
			Array<T>::m_array = new T[Array<T>::m_maxSize];
			memset(Array<T>::m_array, 0, sizeof(T) * Array<T>::m_maxSize);

			Array<T>::m_growSize = ((growBy > 0) ? growBy : 0);
		}
	}

	// Insertion -- Big-O = O(N)
	void push(T val) override
	{
		assert(Array<T>::m_array != nullptr);

		if (Array<T>::m_numElements >= Array<T>::m_maxSize)
		{
			Array<T>::Expand();
		}

		int i, k;	// i - Index to be inserted. k - Used for shifting purposes
		// Step 1: Find the index to insert val
		for (i = 0; i < Array<T>::m_numElements; i++)
		{
			if (Array<T>::m_array[i] > val)
			{
				break;
			}
		}

		// Step 2: Shift everything to the right of the index(i) forward by one. Work backwards
		for (k = Array<T>::m_numElements; k > i; k--)
		{
			Array<T>::m_array[k] = Array<T>::m_array[k - 1];
		}

		// Step 3: Insert val into the array at index
		Array<T>::m_array[i] = val;

		Array<T>::m_numElements++;

		// return i;
	}

	int search(T searchKey) override
	{
		return binarySearch(searchKey, 0, Array<T>::m_numElements - 1);
	}
private:
	// Recursive Binary Search
	int binarySearch(T searchKey, int lowerBound, int upperBound)
	{
		assert(Array<T>::m_array != nullptr);
		assert(lowerBound >= 0);
		assert(upperBound < Array<T>::m_numElements);

		int current = (lowerBound + upperBound) >> 1;

		if (Array<T>::m_array[current] == searchKey)
		{
			return current;
		}

		else if (lowerBound > upperBound)
		{
			return -1;
		}

		else
		{
			if (Array<T>::m_array[current] < searchKey)
			{
				return binarySearch(searchKey, current + 1, upperBound);
			}
			else
			{
				return binarySearch(searchKey, lowerBound, current - 1);
			}
		}

		return -1;
	}
};