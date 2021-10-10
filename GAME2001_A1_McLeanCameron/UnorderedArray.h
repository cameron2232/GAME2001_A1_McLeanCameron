#pragma once
#include <cassert>
#include "Array.h"
template<class T>
class UnorderedArray:public Array<T>
{
public:
	// Constructor
	UnorderedArray(int size, int growBy = 1) :
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

	// Insertion
	void push(T val) override
	{
		assert(m_array != nullptr); 

		if (m_numElements >= m_maxSize)	
		{
			Array<T>::Expand();
		}

		m_array[m_numElements] = val;
		m_numElements++;
	}

	int search(T val) override
	{
		assert(m_array != nullptr);

		for (int i = 0; i < m_numElements; i++)
		{
			if (m_array[i] == val)
			{
				return i;	
			}
		}

		return -1;
	}

	// Bubble Sort -- Big O = O(N^2)
	void BubbleSort()
	{
		assert(m_array != nullptr);

		T temp;

		for (int k = m_numElements - 1; k > 0; k--)
		{
			for (int i = 0; i < k; i++)	 
			{
			
				if (m_array[i] > m_array[i + 1])
				{
					
					temp = m_array[i];
					m_array[i] = m_array[i + 1];
					m_array[i + 1] = temp;
				}
			}
		}
	}
	// Selection Sort -- Big O = O(N^2)
	void SelectionSort()
	{
		assert(m_array != nullptr);

		T temp;	
		int min = 0;	

		
		for (int k = 0; k < m_numElements; k++)
		{
			min = k;	

			
			for (int i = k + 1; i < m_numElements; i++)
			{
				
				if (m_array[i] < m_array[min])
				{
					
					min = i;
				}
			}

		
			if (m_array[k] > m_array[min])
			{

				temp = m_array[k];
				m_array[k] = m_array[min];
				m_array[min] = temp;
			}
		}
	}
	// Insertion Sort -- Big O = O(N^2)
	void InsertionSort()
	{
		assert(m_array != nullptr);

		T temp;
		int i = 0;

		for (int k = 1; k < m_numElements; k++) 
		{
			temp = m_array[k];
			i = k;

			while (i > 0 && m_array[i - 1] >= temp)
			{
				m_array[i] = m_array[i - 1];
				i--;
			}

			m_array[i] = temp;
		}
	}
	// Merge Srot -- Big O = O(N logN)
	void MergeSort()
	{
		assert(m_array != nullptr);

		T* tempArray = new T[m_numElements];
		assert(tempArray != nullptr);

		MergeSort(tempArray, 0, m_numElements - 1);
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
			
			if (m_array[low] < m_array[mid])
			{
				tempArray[index++] = m_array[low++];	
			}
			else
			{
				tempArray[index++] = m_array[mid++];	
			}
		}

		while (low <= tempMid) 
		{
			tempArray[index++] = m_array[low++];
		}
		while (mid <= upper) 
		{
			tempArray[index++] = m_array[mid++];
		}

		
		for (int i = 0; i < upper - tempLow + 1; i++)
		{
			m_array[tempLow + i] = tempArray[i];
		}
	}
};
