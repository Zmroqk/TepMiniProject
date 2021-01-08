#pragma once
#include "RefCounter.h"

template <typename T>
class SmartPointer
{
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	SmartPointer();

	/// <summary>
	/// Parameter constructor init smartpointer with data
	/// </summary>
	/// <param name="pPointer">Pointer to data to keep</param>
	SmartPointer(T* pPointer);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="pOther">Other smart pointer</param>
	inline SmartPointer(const SmartPointer<T>& pOther) { CopyData(pOther); }

	/// <summary>
	/// Move constructor
	/// </summary>
	/// <param name="pOther">Other smart pointer</param>
	inline SmartPointer(SmartPointer<T>&& pOther) { MoveData(pOther); }

	inline ~SmartPointer() { CheckCounter(); }

	void operator=(const SmartPointer<T>& pOther);
	inline T& operator*() { return(*pPointer); }
	inline T* operator->() { return(pPointer); }
	inline T** operator&() { return(&pPointer); }
	inline operator T* () { return(pPointer); }
	inline operator T** () { return(&pPointer); }
	inline operator T& () { return(*pPointer); }
	//inline T* operator()() { return(pPointer); }

	/// <summary>
	/// Set new data for this pointer
	/// </summary>
	/// <param name="newData">Pointer to new data</param>
	void SetPointer(T* newData);

	/// <summary>
	/// Duplicate this pointer (create copy of data)
	/// </summary>
	/// <returns>New smart pointer with copied data</returns>
	SmartPointer<T> Duplicate();

private:
	/// <summary>
	/// Check if counter reaches 0
	/// </summary>
	void CheckCounter();

	/// <summary>
	/// Copy all data from other 
	/// </summary>
	/// <param name="pOther">Other smart pointer to copy</param>
	void CopyData(const SmartPointer<T>& pOther);

	/// <summary>
	/// Move all data from other 
	/// </summary>
	/// <param name="pOther">Other smart pointer to move</param>
	void MoveData(SmartPointer<T>& pOther);

	/// <summary>
	/// Copy all reference
	/// </summary>
	/// <param name="pOther">Other smart pointer </param>
	void CopyRef(const SmartPointer<T>& pOther);

	/// <summary>
	/// Counter for smart pointer
	/// </summary>
	RefCounter* pCounter;

	/// <summary>
	/// Data of smart pointer
	/// </summary>
	T* pPointer;
};

template<typename T>
SmartPointer<T>::SmartPointer()
{
	this->pPointer = nullptr;
	this->pCounter = new RefCounter();
	this->pCounter->Add();
}

template<typename T>
SmartPointer<T>::SmartPointer(T* pPointer)
{
	this->pPointer = pPointer;
	this->pCounter = new RefCounter();
	this->pCounter->Add();
}


template<typename T>
void SmartPointer<T>::SetPointer(T* newData)
{
	this->CheckCounter();
	this->pPointer = newData;
	this->pCounter = new RefCounter();
	this->pCounter->Add();
}

template<typename T>
void SmartPointer<T>::operator=(const SmartPointer<T>& pOther)
{
	this->CheckCounter();
	CopyData(pOther);
}

template<typename T>
void SmartPointer<T>::CheckCounter()
{
	if (pCounter == nullptr)
		return;
	if (pCounter->Dec() == 0)
	{
		if(this->pPointer != nullptr)
			delete pPointer;
		if (this->pCounter != nullptr)
			delete pCounter;
		this->pPointer = nullptr;
		this->pCounter = nullptr;
	}
}

template<typename T>
void SmartPointer<T>::CopyRef(const SmartPointer<T>& pOther)
{
	this->pPointer = pOther.pPointer;
	this->pCounter = pOther.pCounter;
}
template<typename T>
void SmartPointer<T>::CopyData(const SmartPointer<T>& pOther)
{
	this->CopyRef(pOther);
	this->pCounter->Add();
}
template<typename T>
void SmartPointer<T>::MoveData(SmartPointer<T>& pOther)
{
	this->CopyRef(pOther);
	pOther.pPointer = nullptr;
	pOther.pCounter = nullptr;
	
}
template<typename T>
SmartPointer<T> SmartPointer<T>::Duplicate() {
	return std::move(SmartPointer<T>(new T(*this->pPointer)));
}
