#pragma once
#include <exception>

/// <summary>
/// Allocate memory for array
/// </summary>
/// <typeparam name="T">Type of data to allocate for</typeparam>
/// <param name="size">Size of array</param>
/// <returns>Pointer to new array if successful</returns>
template <typename T>
T* AllocateArray(size_t size) {
	try {
		return new T[size];
	}
	catch(std::exception e) {
		return nullptr;
	}
}

/// <summary>
/// Allocate memory for two dimensional array
/// </summary>
/// <typeparam name="T">Type of data to allocate for</typeparam>
/// <param name="firstDimension">Size for first dimension</param>
/// <param name="secondDimension">Size for second dimension</param>
/// <returns>Pointer to new two dimensionalArray if successful</returns>
template <typename T>
T** AllocateTwoDimensionalArray(size_t firstDimension, size_t secondDimension) {
	try {
		T** newArray = new T* [firstDimension];
		for (size_t i = 0; i < firstDimension; i++) {
			newArray[i] = new T[secondDimension];
		}
		return newArray;
	}
	catch (std::exception e) {
		return nullptr;
	}
}

/// <summary>
/// Deallocate memory of array
/// </summary>
/// <typeparam name="T">Type of data to deallocate</typeparam>
/// <param name="arr">Array to deallocate</param>
/// <returns>True if deallocation is successful</returns>
template <typename T>
bool DeallocateArray(T*& arr) {
	if (arr != nullptr) {
		delete[] arr;
		arr = nullptr;
		return true;
	}
	return false;
}

/// <summary>
/// Deallocate memory of two dimensional array
/// </summary>
/// <typeparam name="T">Type of data to deallocate</typeparam>
/// <param name="arr">Two dimensional array to deallocate</param>
/// <param name="firstDimension"></param>
/// <returns>True if deallocation is successful</returns>
template <typename T>
bool DeallocateTwoDimensionalArray(T*** arr, size_t firstDimension) {
	if (*arr != nullptr) {
		for (size_t i = 0; i < firstDimension; i++) {
			if ((*arr)[i] != nullptr) {
				delete[] (*arr)[i];
			}
		}
		delete[] *arr;
		*arr = nullptr;
		return true;
	}
	return false;
}

/// <summary>
/// Create copy of provided array
/// </summary>
/// <typeparam name="T">Type of data to copy</typeparam>
/// <param name="arr">Array to copy</param>
/// <param name="firstDimension">First dimension of two dimensional array</param>
/// <param name="secondDimension">Second dimension of two dimensional array</param>
/// <returns></returns>
template <typename T>
T** CopyTwoDimensionalArray(T** arr, size_t firstDimension, size_t secondDimension) {
	T** newArray = AllocateTwoDimensionalArray<T>(firstDimension, secondDimension);
	for (size_t i = 0; i < firstDimension; i++) {
		for (size_t j = 0; j < secondDimension; j++) {
			newArray[i][j] = arr[i][j];
		}
	}
	return newArray;
}
