#pragma once
#include <cassert>
#include "Array.h"
template<class T>
class OrderedArray:public Array<T>
{
public:
	// Constructor
	OrderedArray(int size, int growBy = 1) :
		m_array(NULL), m_maxSize(0), m_growSize(0), m_numElements(0)
	{
		if (size)	
		{
			m_maxSize = size;
			m_array = new T[m_maxSize];		
			memset(m_array, 0, sizeof(T) * m_maxSize);	

			m_growSize = ((growBy > 0) ? growBy : 0);
		}
	}

	// Insertion -- Big-O = O(N)
	void push(T val) override
	{
		assert(m_array != nullptr);

		if (m_numElements >= m_maxSize)
		{
			Array<T>::Expand();
		}

		int i, k;	// i - Index to be inserted. k - Used for shifting purposes
		// Step 1: Find the index to insert val
		for (i = 0; i < m_numElements; i++)
		{
			if (m_array[i] > val)
			{
				break;
			}
		}

		// Step 2: Shift everything to the right of the index(i) forward by one. Work backwards
		for (k = m_numElements; k > i; k--)
		{
			m_array[k] = m_array[k - 1];
		}

		// Step 3: Insert val into the array at index
		m_array[i] = val;

		m_numElements++;

		// return i;
	}

	int search(T searchKey) override
	{
		return binarySearch(searchKey, 0, m_numElements - 1);
	}
private:
	// Recursive Binary Search
	int binarySearch(T searchKey, int lowerBound, int upperBound)
	{
		assert(m_array != nullptr);
		assert(lowerBound >= 0);
		assert(upperBound < m_numElements);

		int current = (lowerBound + upperBound) >> 1;

		if (m_array[current] == searchKey)
		{
			return current;
		}

		else if (lowerBound > upperBound)
		{
			return -1;
		}

		else
		{
			if (m_array[current] < searchKey)
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