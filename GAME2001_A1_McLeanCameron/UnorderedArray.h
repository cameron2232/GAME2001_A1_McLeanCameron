#pragma once
#include <cassert>
#include "Array.h"
#include <cstring>

template<class T>
class UnorderedArray:public Array<T>
{
public:
	// Constructor
	UnorderedArray(int size, int growBy = 1)
	{
		if (size)
		{
			Array<T>::m_maxSize = size;
			Array<T>::m_array = new T[Array<T>::m_maxSize];
			memset(Array<T>::m_array, 0, sizeof(T) * Array<T>::m_maxSize);

			Array<T>::m_growSize = ((growBy > 0) ? growBy : 0);
		}
	}

	// Insertion
	void push(T val) override
	{
		assert(Array<T>::m_array != nullptr);

		if (Array<T>::m_numElements >= Array<T>::m_maxSize)
		{
			Array<T>::Expand();
		}

		Array<T>::m_array[Array<T>::m_numElements] = val;
		Array<T>::m_numElements++;
	}

	int search(T val) override
	{
		assert(Array<T>::m_array != nullptr);

		for (int i = 0; i < Array<T>::m_numElements; i++)
		{
			if (Array<T>::m_array[i] == val)
			{
				return i;	
			}
		}

		return -1;
	}

	// Bubble Sort -- Big O = O(N^2)
	void BubbleSort()
	{
		assert(Array<T>::m_array != nullptr);

		T temp;

		for (int k = Array<T>::m_numElements - 1; k > 0; k--)
		{
			for (int i = 0; i < k; i++)	 
			{
			
				if (Array<T>::m_array[i] > Array<T>::m_array[i + 1])
				{
					
					temp = Array<T>::m_array[i];
					Array<T>::m_array[i] = Array<T>::m_array[i + 1];
					Array<T>::m_array[i + 1] = temp;
				}
			}
		}
	}
	// Selection Sort -- Big O = O(N^2)
	void SelectionSort()
	{
		assert(Array<T>::m_array != nullptr);

		T temp;	
		int min = 0;	

		
		for (int k = 0; k < Array<T>::m_numElements; k++)
		{
			min = k;	

			
			for (int i = k + 1; i < Array<T>::m_numElements; i++)
			{
				
				if (Array<T>::m_array[i] < Array<T>::m_array[min])
				{
					
					min = i;
				}
			}

		
			if (Array<T>::m_array[k] > Array<T>::m_array[min])
			{

				temp = Array<T>::m_array[k];
				Array<T>::m_array[k] = Array<T>::m_array[min];
				Array<T>::m_array[min] = temp;
			}
		}
	}
	// Insertion Sort -- Big O = O(N^2)
	void InsertionSort()
	{
		assert(Array<T>::m_array != nullptr);

		T temp;
		int i = 0;

		for (int k = 1; k < Array<T>::m_numElements; k++)
		{
			temp = Array<T>::m_array[k];
			i = k;

			while (i > 0 && Array<T>::m_array[i - 1] >= temp)
			{
				Array<T>::m_array[i] = Array<T>::m_array[i - 1];
				i--;
			}

			Array<T>::m_array[i] = temp;
		}
	}
	// Merge Srot -- Big O = O(N logN)
	void MergeSort()
	{
		assert(Array<T>::m_array != nullptr);

		T* tempArray = new T[Array<T>::m_numElements];
		assert(tempArray != nullptr);

		MergeSort(tempArray, 0, Array<T>::m_numElements - 1);
		delete[] tempArray;
	}
	
private:
	void MergeSort(T* tempArray, int lowerBound, int upperBound)
	{
		if (lowerBound == upperBound)
		{
			return;
		}

		int mid = (lowerBound + upperBound) >> 1;

		MergeSort(tempArray, lowerBound, mid);	
		MergeSort(tempArray, mid + 1, upperBound); 

		// Merge
		Merge(tempArray, lowerBound, mid + 1, upperBound);
	}
	void Merge(T* tempArray, int low, int mid, int upper)
	{
		// Lowerbound, Mid+1, Upperbound
		int tempLow = low, tempMid = mid - 1;
		int index = 0;

		while (low <= tempMid && mid <= upper)
		{
			
			if (Array<T>::m_array[low] < Array<T>::m_array[mid])
			{
				tempArray[index++] = Array<T>::m_array[low++];
			}
			else
			{
				tempArray[index++] = Array<T>::m_array[mid++];
			}
		}

		while (low <= tempMid) 
		{
			tempArray[index++] = Array<T>::m_array[low++];
		}
		while (mid <= upper) 
		{
			tempArray[index++] = Array<T>::m_array[mid++];
		}

		
		for (int i = 0; i < upper - tempLow + 1; i++)
		{
			Array<T>::m_array[tempLow + i] = tempArray[i];
		}
	}
};
