#include <iostream>
#include "cArray.h"

int main()
{
	try
	{
		cArray<int> arr, arr2;

		std::cout << "Add" << std::endl;

		for (int i = 0; i < 10; i++)
			arr.Add(i);

		for (int i = 0; i < arr.GetCount(); i++)
			std::cout << arr[i] << std::endl;

		std::cout << std::endl << "Copy" << std::endl;

		arr2.Copy(&arr);

		for (int i = 0; i < arr2.GetCount(); i++)
			std::cout << arr2[i] << std::endl;

		std::cout << std::endl << "Set size" << std::endl;

		arr2.SetSize(5);

		for (int i = 0; i < arr2.GetCount(); i++)
			std::cout << arr2[i] << std::endl;

		std::cout << std::endl<< "Append" << std::endl;

		arr2.Append(&arr);

		for (int i = 0; i < arr2.GetCount(); i++)
			std::cout << arr2[i] << std::endl;

		std::cout << std::endl << "RemoveAt" << std::endl;

		arr2.RemoveAt(5);

		for (int i = 0; i < arr2.GetCount(); i++)
			std::cout << arr2[i] << std::endl;

		std::cout << std::endl << "GetUpperBound" << std::endl;

		arr2.RemoveAt(arr2.GetUpperBound());

		for (int i = 0; i < arr2.GetCount(); i++)
			std::cout << arr2[i] << std::endl;

		std::cout << std::endl << std::endl;

	}
	catch (const std::bad_alloc &exc)
	{
		std::cout << "Allocation failed: " << exc.what() << std::endl;
	}
	catch (std::out_of_range &exc)
	{
		std::cout << "Out of range: " << exc.what() << std::endl;
	}

	system("PAUSE");
	return 0;
}