#pragma once
#include <algorithm>
#include <stdexcept>
#include <cmath>

template<typename ElemType>
class cArray
{
	//The minimum number of element slots to allocate if a size increase is necessary. 
	#define GROWBY 10

	private:
		ElemType *Data;
		int Size, Count, UpperBound;

		ElemType *_realloc(ElemType *&_data, int _size, int n_size);

			
	public:
		//Constructs an empty array.
		cArray();
		cArray(int);
		~cArray();

		//Operators
		//Sets or gets the element at the specified index.
		ElemType& operator[] (int) throw(std::out_of_range);
		

		//Attributes
		//Gets the number of elements in this array.
		int GetSize() const;
		//Gets the number of elements in this array.
		int GetCount() const;
		//Returns the largest valid index.
		int GetUpperBound() const;
		
		//Determines whether the array is empty.
		bool IsEmpty() const;

		//Establishes the size of an empty or existing array; allocates memory if necessary.
		void SetSize(int nNewSize);
	


		//Operations
		//Frees all unused memory above the current upper bound.
		//This function has no effect on the upper bound of the array.
		void FreeExtra();

		//Removes all the elements from this array.
		void RemoveAll();

		//Element Access
		//Returns the value at a given index.
		ElemType GetAt(int) const throw(std::out_of_range);
		//Sets the value for a given index; array not allowed to grow.
		void SetAt(const ElemType &n, int indx) throw(std::out_of_range);

		//Growing the Array
		//Adds an element to the end of the array; grows the array if necessary.
		void Add(ElemType);
		//Appends another array to the array; grows the array if necessary
		void Append(cArray *);
		//Copies another array to the array; grows the array if necessary.
		void Copy(cArray *);

		//Insertion/Removal
		//Inserts an element at a specified index.
		void InsertAt(ElemType n, int indx) throw(std::out_of_range);
		//Removes an element at a specific index.
		void RemoveAt(int) throw(std::out_of_range);

};

#pragma region cArray

template<typename ElemType>
cArray<ElemType>::cArray(int _size)
{
	Size = _size;
	Count = 0;
	Data = new ElemType[_size];
	UpperBound = -1;
}

template<typename ElemType>
cArray<ElemType>::cArray()
{
	Size = GROWBY;
	Count = 0;
	Data = new ElemType[GROWBY];
	UpperBound = -1;
}

template<typename ElemType>
cArray<ElemType>::~cArray()
{
	delete[] Data;
}

////////////////////////////////////////////////////////////

template<typename ElemType>
ElemType& cArray<ElemType>::operator[] (int indx) throw(std::out_of_range)
{

	if (indx < 0 || indx > UpperBound)
	{
		throw std::out_of_range("Ooops!");
	}

	return Data[indx];
}

////////////////////////////////////////////////////////////

template<typename ElemType>
inline ElemType *cArray<ElemType>::_realloc(ElemType *&_data, int _size, int n_size)
{
	ElemType *new_data = new ElemType[n_size];

	n_size > _size ? memcpy_s(new_data, n_size * sizeof(ElemType), _data, _size * sizeof(ElemType)) : 
		memcpy_s(new_data, n_size * sizeof(ElemType), _data, n_size * sizeof(ElemType));

	delete[] _data;
	_data = new_data;
	return new_data;
}

////////////////////////////////////////////////////////////

template<typename ElemType>
int cArray<ElemType>::GetSize() const
{
	return Size;
}

template<typename ElemType>
int cArray<ElemType>::GetCount() const
{
	return Count;
}

template<typename ElemType>
int cArray<ElemType>::GetUpperBound() const
{
	return UpperBound;
}

////////////////////////////////////////////////////////////

template<typename ElemType>
bool cArray<ElemType>::IsEmpty() const
{
	return Count == 0;
}

////////////////////////////////////////////////////////////

template<typename ElemType>
void cArray<ElemType>::SetSize(int nNewSize)
{
	if (Size > nNewSize)
	{
		if (Count > nNewSize) 
		{
			Count = nNewSize;
			UpperBound = nNewSize - 1;
		}
	}
	
	_realloc(Data, Size, nNewSize);
	Size = nNewSize;
}

////////////////////////////////////////////////////////////

template<typename ElemType>
void cArray<ElemType>::FreeExtra()
{
	SetSize(UpperBound);
}

////////////////////////////////////////////////////////////

template<typename ElemType>
void cArray<ElemType>::RemoveAll()
{
	Size = 0;
	Count = 0;
	UpperBound = -1;
	delete[] Data;
}

////////////////////////////////////////////////////////////

template<typename ElemType>
ElemType cArray<ElemType>::GetAt(int indx) const throw(std::out_of_range)
{
	if (indx < 0 || indx > UpperBound)
	{
		throw throw std::out_of_range("Ooops!");
	}

	return Data[indx];
}

template<typename ElemType>
void cArray<ElemType>::SetAt(const ElemType &n, int indx) throw(std::out_of_range)
{
	if (indx < 0 || indx > UpperBound)
	{
		throw throw std::out_of_range("Ooops!");
	}

	Data[indx] = n;
}

////////////////////////////////////////////////////////////

template<typename ElemType>
void cArray<ElemType>::Add(ElemType n)
{
	if (++Count >= Size)
		SetSize(Size + GROWBY);

	UpperBound++;
	Data[UpperBound] = n;
}

////////////////////////////////////////////////////////////

template<typename ElemType>
void cArray<ElemType>::Append(cArray *arr)
{
	if (arr->Count + Count > Size)
		SetSize(GROWBY * ceil( ((float)Count + (float)arr->Count) / GROWBY));

	std::copy(arr->Data, arr->Data + arr->UpperBound + 1, Data + UpperBound + 1);
	Count += arr->Count;
	UpperBound = Count - 1;
}

////////////////////////////////////////////////////////////

template<typename ElemType>
void cArray<ElemType>::Copy(cArray *arr)
{
	if (arr->GetSize() > Size)
		SetSize(GROWBY * ceil((float)arr->GetSize() / GROWBY));

	std::copy(arr->Data, arr->Data + arr->UpperBound + 1, Data);
	Count = arr->Count;
	UpperBound = arr->UpperBound;
}

////////////////////////////////////////////////////////////

template<typename ElemType>
void cArray<ElemType>::InsertAt(ElemType n, int indx) throw(std::out_of_range)
{
	if (indx < 0 || indx > UpperBound)
	{
		throw throw std::out_of_range("Ooops!");
	}

	if (++Count >= Size)
		SetSize(Size + GROWBY);
	
	std::rotate(std::begin(Data) + indx, std::begin(Data) + UpperBound, std::end(Data) + UpperBound + 1);

	Data[indx] = n;
	Count++;
	UpperBound++;
}

template<typename ElemType>
void cArray<ElemType>::RemoveAt(int indx) throw(std::out_of_range)
{
	if (indx < 0 || indx > UpperBound)
	{
		throw std::out_of_range("Ooops!");
	}

	std::rotate(Data + indx, Data + indx + 1, Data + UpperBound + 1);

	Count--;
	UpperBound--;
}

#pragma endregion
