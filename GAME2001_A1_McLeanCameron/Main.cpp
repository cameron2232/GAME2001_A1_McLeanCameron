#include "UnorderedArray.h"
#include "OrderedArray.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "Merge Sort Algorithm" << endl;

	UnorderedArray<int> array(5);
	array.push(80);
	array.push(64);
	array.push(99);
	array.push(76);
	array.push(5);

	OrderedArray<int> orderArray(3);
	orderArray.push(20);
	orderArray.push(105);
	orderArray.push(20);
	orderArray.push(24);

	cout << "Ordered Array: ";
	for (int i = 0; i < orderArray.GetSize(); i++)
	{
		cout << " " << orderArray[i];
	}

	cout << "\n\nBefore Sorting: ";
	for (int i = 0; i < array.GetSize(); i++)
	{
		cout << " " << array[i];
	}
	cout << endl;

	// Call our sort
	array.MergeSort();

	cout << "After sorting: ";
	for (int i = 0; i < array.GetSize(); i++)
	{
		cout << " " << array[i];
	}

	cout << endl << endl;

	cout << array.GetSize() << "  " << array.m_growSize << "\n";
	array.Expand();
	cout << array.GetSize() << "  " << array.m_growSize << "\n";
	array.Expand();
	cout << array.GetSize() << "  " << array.m_growSize << "\n";
	array.Expand();

	return 0;
}