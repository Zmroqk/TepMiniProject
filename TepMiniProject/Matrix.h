#pragma once
/*
* !!!!!!!!!!!!!!!!!!!!!!!	IMPORTANT	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
* All public methods that contains argument for output will output result there.
* If no output was given, methods will operate on instance of object they were called on.
* Standard return contains only information about status of operation.
* If operation is successful it will return MatrixStatus::Success, other statuses will inform you 
*	there was an error during operation.
*/

#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "MatrixErrorCodes.h"
#include "HelperMethods.h"
#include "SmartPointer.h"
#include "ReadMatrix.h"
#include "MatrixException.h"

/// <summary>
/// Default matrix size
/// </summary>
const size_t MATRIXDEFAULTSIZE = 5;

/// <summary>
/// Default size in columns of vector matrix
/// </summary>
const size_t VECTORCOLUMNSIZE = 1;

/// <summary>
/// Buffer size for to string
/// </summary>
const size_t BUFFER_SIZE = 15;

/// <summary>
/// Default format for int
/// </summary>
const std::string DEFAULT_FORMAT_INT = "%-10d ";

/// <summary>
/// Default format for float and double
/// </summary>
const std::string DEFAULT_FORMAT_FLOAT_AND_DOUBLE = "%10.2f ";

/// <summary>
/// Default format for type T
/// </summary>
const std::string DEFAULT_FORMAT_TYPE_T = "%-10s ";

template <typename T>
class Matrix {
public:
//--------------------------------------------------------------------------------------------CONSTRUCTORS--------------------------------------------------------------------------------------------------------------
	
	/// <summary>
	/// Default constructor
	/// </summary>
	Matrix();

	/// <summary>
	/// Constructor with specific matrix size
	/// </summary>
	/// <param name="firstDimensionSize">First dimension for matrix</param>
	/// <param name="secondDimensionSize">Second dimension for matrix</param>
	Matrix(size_t firstDimensionSize, size_t secondDimensionSize);

	/// <summary>
	/// Read matrix from file
	/// </summary>
	/// <param name="path">Path to file</param>
	inline Matrix(const std::string& path) { this->SetNewMatrixFromFile(path); }

	/// <summary>
	/// Constructor with specific matrix, and it's size
	/// </summary>
	/// <param name="matrix">Matrix for this instance</param>
	/// <param name="firstDimensionSize">First dimension for matrix</param>
	/// <param name="secondDimensionSize">Second dimension for matrix</param>	
	inline Matrix(T** matrix, size_t firstDimensionSize, size_t secondDimensionSize) { this->SetNewMatrix(matrix, firstDimensionSize, secondDimensionSize); }

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="otherMatrix">Other instance to copy from</param>
	inline Matrix(const Matrix<T>& otherMatrix) { this->ppMatrix = nullptr; this->CopyData(otherMatrix); }

	/// <summary>
	/// Move constructor
	/// </summary>
	/// <param name="otherMatrix">Other instance to move from</param>
	inline Matrix(Matrix<T>&& otherMatrix) { this->ppMatrix = nullptr; this->MoveData(otherMatrix); }

	/// <summary>
	/// Destrructor
	/// </summary>
	inline ~Matrix() { this->RemoveData(); }

//-------------------------------------------------------------------------------------------METHODS-----------------------------------------------------------------------------------------------------------------
	
	/// <summary>
	/// Add two matrices together
	/// </summary>
	/// <param name="otherMatrix">Matrix to use when adding to this one</param>
	/// <param name="outMatrix">New matrix output, if nullptr provided operation will operate on this instance</param>
	/// <returns>Operation status</returns>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::IncorrectFirstDimension"/>
	/// <exception cref="MatrixStatus::IncorrectSecondDimension"/>
	/// <exception cref="MatrixStatus::UnknownError"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus Add(const Matrix<T>& otherMatrix, Matrix<T>** outMatrix = nullptr);

	/// <summary>
	/// Substract matrix from this instance
	/// </summary>
	/// <param name="otherMatrix">Matrix to use when substracting</param>
	/// <param name="outMatrix">New matrix output, if nullptr provided operation will operate on this instance</param>
	/// <returns>Operation status</returns>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::IncorrectFirstDimension"/>
	/// <exception cref="MatrixStatus::IncorrectSecondDimension"/>
	/// <exception cref="MatrixStatus::UnknownError"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus Substract(const Matrix<T>& otherMatrix, Matrix<T>** outMatrix = nullptr);

	/// <summary>
	/// Multiply this matrix with some value
	/// </summary>
	/// <param name="value">Value with witch matrix should be multiplied</param>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus Multiply(const T& value, Matrix<T>** outMatrix = nullptr);

	/// <summary>
	/// Multiply this matrix with other matrix
	/// </summary>
	/// <param name="otherMatrix">Other matrix used in multiplication</param>
	/// <param name="outMatrix">Matrix where output will be saved</param>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::IncorrectSecondDimension"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus Multiply(const Matrix<T>& otherMatrix, Matrix<T>** outMatrix = nullptr);

	/// <summary>
	/// Create transposition of matrix
	/// </summary>
	/// <param name="outMatrix">Matrix where output will be saved</param>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus Transposition(Matrix<T>** outMatrix = nullptr);

	/// <summary>
	/// Count scalar of two vectors
	/// </summary>
	/// <param name="otherVector">Other vector to use when calculating scalar</param>
	/// <param name="outScalar">Output for scalar value</param>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::IncorrectFirstDimension"/>
	/// <exception cref="MatrixStatus::IncorrectSecondDimension"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus ScalarProduct(const Matrix<T>& otherVector, T* outScalar);

	/// <summary>
	/// Generate matrix values
	/// </summary>
	/// <param name="range">Range for genereting valus</param>
	/// <param name="startValue">Start value for genereting value</param>
	/// <returns>Operation status</returns>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::UnknownError"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus GenerateRandomValues(size_t range, int startValue);

	/// <summary>
	/// Create vector from this matrix using given column
	/// </summary>
	/// <param name="secondDimensionIndex">Index of column to use</param>
	/// <param name="outVector">Vector output</param>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::IncorrectSecondDimension"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus GetVectorByColumn(size_t secondDimensionIndex, Matrix<T>** outVector = nullptr);

	/// <summary>
	/// Create vector from this matrix using given row
	/// </summary>
	/// <param name="firstDimensionIndex">Index of row to use</param>
	/// <param name="outVector">Vector output</param>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::IncorrectSecondDimension"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus GetVectorByRow(size_t firstDimensionIndex, Matrix<T>** outVector = nullptr);

//-----------------------------------------------------------------------------------------------GET----------------------------------------------------------------------------------------------------------------

	/// <summary>
	/// Get pointer to matrix
	/// </summary>
	/// <returns>Pointer to matrix</returns>
	inline const T* const * GetMatrix() const { return this->ppMatrix; }

	/// <summary>
	/// Get value of matrix at given position
	/// </summary>
	/// <param name="firstDimIndex">Index of first dimension</param>
	/// <param name="secondDimIndex">Index of second dimension</param>
	/// <returns>Pointer to value at given position</returns>
	const T* GetValueAtPosition(size_t firstDimIndex, size_t secondDimIndex) const;

	/// <summary>
	/// Get size of first matrix dimension
	/// </summary>
	/// <returns>Size of first dimension</returns>
	inline const size_t GetFirstMatrixDimension() const { return this->firstDimSize; }

	/// <summary>
	/// Get size of second matrix dimension
	/// </summary>
	/// <returns>Size of second dimension</returns>
	inline const size_t GetSecondMatrixDimension() const { return this->secondDimSize; }

	/// <summary>
	/// To string
	/// </summary>
	/// <returns>Matrix as string</returns>
	std::string ToString() const;

	/// <summary>
	/// To string
	/// </summary>
	/// <returns>Matrix as string</returns>
	std::string ToString(const std::string& format, const int bufferSize) const;

//--------------------------------------------------------------------------------------------------SET-------------------------------------------------------------------------------------------------------------

	/// <summary>
	/// Set new matrix with provided matrix
	/// </summary>
	/// <param name="newMatrix">New matrix to set</param>
	/// <param name="firstDimSize">First dimension of new matrix</param>
	/// <param name="secondDimSize">Second dimension of new matrix</param>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus SetNewMatrix(T** newMatrix, size_t firstDimSize, size_t secondDimSize);

	/// <summary>
	/// Set new matrix with provided file
	/// </summary>
	/// <param name="path">Path to file</param>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus SetNewMatrixFromFile(const std::string& path);

	/// <summary>
	/// Set new value at given position in matrix
	/// </summary>
	/// <param name="firstDimIndex">First dimension index</param>
	/// <param name="secondDimIndex">Second dimension index</param>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::IncorrectFirstDimension"/>
	/// <exception cref="MatrixStatus::IncorrectSecondDimension"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus SetValueAtPosition(T& value, size_t firstDimIndex, size_t secondDimIndex);

	/// <summary>
	/// Set values in matrix as indentity matrix with custom values
	/// </summary>
	/// <param name="value">Value to be set on diagonal</param>
	/// <param name="valueForRest">Value to be set everywhere except diagonal</param>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NonSquare"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus SetIdentityMatrix(T& value, T& valueForRest);

//-----------------------------------------------------------------------------------------OPERATORS----------------------------------------------------------------------------------------------------------------------
	
	Matrix<T> operator+(const Matrix<T>& otherMatrix);
	Matrix<T> operator-(const Matrix<T>& otherMatrix);
	Matrix<T> operator*(T value);
	Matrix<T> operator*(const Matrix<T>& otherMatrix);
	inline void operator=(const Matrix<T>& otherMatrix) { this->CopyData(otherMatrix); }
	inline void operator=(Matrix<T>&& otherMatrix) { this->MoveData(otherMatrix); }
	inline bool operator==(const Matrix<T>* otherMatrix) const { return this == otherMatrix; }
	inline bool operator==(const Matrix<T>& otherMatrix) const { return this == &otherMatrix; }
	inline bool operator!=(const Matrix<T>* otherMatrix) const { return !(this == otherMatrix); }
	inline bool operator!=(const Matrix<T>& otherMatrix) const { return !(this == &otherMatrix); }
	inline operator const T* const* () const { return this->GetMatrix(); }
	inline operator const std::string () const { return std::move(this->ToString()); }
	//inline operator const char* () { return this->ToString().c_str(); }

//----------------------------------------------------------------------------------------PRIVATE-----------------------------------------------------------------------------------------------------------------------

private:
	/// <summary>
	/// Copy data from other matrix
	/// </summary>
	/// <param name="otherMatrix">Matrix to use when copying data</param>
	/// <param name="shouldMove">Should move instead of copying?</param>
	void CopyData(const Matrix<T>& otherMatrix);

	/// <summary>
	/// Move data from other matrix to this one
	/// </summary>
	/// <param name="otherMatrix">Matrix to use when moving data</param>
	void MoveData(Matrix<T>& otherMatrix);

	/// <summary>
	/// Remove all data stored
	/// </summary>
	void RemoveData();

	/// <summary>
	/// Do provided operation on every element of this instance and other matrix instance
	/// </summary>
	/// <param name="newMatrix">Matrix where to store operation result</param>
	/// <param name="secondMatrix">Second matrix used in operation</param>
	/// <param name="firstDim">First dimension size</param>
	/// <param name="secondDim">Second dimension size</param>
	/// <param name="operation">Operation to execute</param>
	void DoOperation(T** newMatrix, T** secondMatrix, size_t firstDim, size_t secondDim, T (*operation)(T i, T j));

	/// <summary>
	/// Do provided operation on every element of this instance and some provided value
	/// </summary>
	/// <param name="newMatrix">Matrix where to store operation result</param>
	/// <param name="value">Value to use during operation</param>
	/// <param name="firstDim">First dimension size</param>
	/// <param name="secondDim">Second dimension size</param>
	/// <param name="operation">Operation to execute</param>
	void DoOperation(T** newMatrix, const T& value, size_t firstDim, size_t secondDim, T(*operation)(T i, T j));

	/// <summary>
	/// Create new matrix
	/// </summary>
	/// <param name="outMatrix">Matrix where data should be outputed</param>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::UnknownError"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus CreateNewMatrix(T*** outMatrix);

	/// <summary>
	/// Compare data of two matrices
	/// </summary>
	/// <param name="otherMatrix">Other matrix to copmare with</param>
	/// <returns></returns>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::IncorrectFirstDimension"/>
	/// <exception cref="MatrixStatus::IncorrectSecondDimension"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus CompareData(const Matrix<T>& otherMatrix) const;

	/// <summary>
	/// Check if this instance contains data about matrix
	/// </summary>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus CheckIfDataExists() const;

	/// <summary>
	/// Check if this instance and other instance contains data about matrix
	/// </summary>
	/// <param name="otherMatrix">Other instance to check</param>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus CheckIfDataExists(const Matrix<T>& otherMatrix) const;

	/// <summary>
	/// Copmare two object and allocate data for new matrix if compare is succesfull
	/// </summary>
	/// <param name="otherMatrix">Other instance to check</param>
	/// <param name="outMatrix">Output for new matrix</param>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::IncorrectFirstDimension"/>
	/// <exception cref="MatrixStatus::IncorrectSecondDimension"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus CompareAndAllocate(const Matrix<T>& otherMatrix, T*** outMatrix);
	
	/// <summary>
	/// Decide if new matrix should be outputed or saved in this instance
	/// </summary>
	/// <param name="outMatrix">Output matrix</param>
	/// <param name="newMatrix">New matrix to save</param>
	/// <param name="firstDimensionSize">First dimension size</param>
	/// <param name="secondDimensionSize">Second dimension size</param>
	/// <exception cref="MatrixStatus::NoDataProvided"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus DecideWhereToSave(Matrix<T>** outMatrix, T** newMatrix, size_t firstDimensionSize, size_t secondDimensionSize);

	/// <returns></returns>
	/// <summary>
	/// Generate matrix values
	/// </summary>
	/// <param name="range">Range for genereting valus</param>
	/// <param name="startValue">Start value for genereting value</param>
	/// <param name="randSchema">Schema for genereting values</param>
	/// <returns>Operation status</returns>
	/// <exception cref="MatrixStatus::NoMatrix"/>
	/// <exception cref="MatrixStatus::UnknownError"/>
	/// <exception cref="MatrixStatus::Success"/>
	MatrixStatus GenerateRandomValues(size_t range, int startValue, T(*randSchema)(size_t, int));

	/// <summary>
	/// Matrix
	/// </summary>
	T** ppMatrix;

	/// <summary>
	/// First dimension of matrix
	/// </summary>
	size_t firstDimSize;

	/// <summary>
	/// Second dimension of matrix
	/// </summary>
	size_t secondDimSize;
};
//===============================================================================================================================================================================================================================
//===============================================================================================================================================================================================================================
//===============================================================================================================================================================================================================================

//------------------------------------------------------------------------------------------CONSTRUCTORS-------------------------------------------------------------------------------------------------------------
template <typename T>
Matrix<T>::Matrix(){ 
	this->ppMatrix = AllocateTwoDimensionalArray<T>(MATRIXDEFAULTSIZE, MATRIXDEFAULTSIZE);
	this->firstDimSize = MATRIXDEFAULTSIZE;
	this->secondDimSize = MATRIXDEFAULTSIZE;
}
	
template<typename T>
Matrix<T>::Matrix(size_t firstDimensionSize, size_t secondDimensionSize)
{
	this->ppMatrix = AllocateTwoDimensionalArray<T>(firstDimensionSize, secondDimensionSize);
	this->firstDimSize = firstDimensionSize;
	this->secondDimSize = secondDimensionSize;
	if (secondDimensionSize == VECTORCOLUMNSIZE && firstDimensionSize != secondDimensionSize)
		this->Transposition();
}

//-------------------------------------------------------------------------------------------METHODS-----------------------------------------------------------------------------------------------------------------
template<typename T>
MatrixStatus Matrix<T>::Add(const Matrix<T>& otherMatrix, Matrix<T>** outMatrix)
{
	T** newMatrix = nullptr;
	MatrixStatus status = this->CompareAndAllocate(otherMatrix, &newMatrix);
	if (status != MatrixStatus::Success)
		return status;
	this->DoOperation(newMatrix, otherMatrix.ppMatrix, this->firstDimSize, this->secondDimSize, [](T i, T j) { return i + j; });
	return this->DecideWhereToSave(outMatrix, newMatrix, this->firstDimSize, this->secondDimSize);
}

template<typename T>
MatrixStatus Matrix<T>::Substract(const Matrix<T>& otherMatrix, Matrix<T>** outMatrix)
{
	T** newMatrix = nullptr;
	MatrixStatus status = this->CompareAndAllocate(otherMatrix, &newMatrix);
	if (status != MatrixStatus::Success)
		return status;
	this->DoOperation(newMatrix, otherMatrix.ppMatrix, this->firstDimSize, this->secondDimSize, [](T i, T j) { return i - j; });
	return this->DecideWhereToSave(outMatrix, newMatrix, this->firstDimSize, this->secondDimSize);
}

template<typename T>
MatrixStatus Matrix<T>::Multiply(const T& value, Matrix<T>** outMatrix)
{
	if (this->ppMatrix == nullptr) 
		return MatrixStatus::NoMatrix;
	T** newMatrix = AllocateTwoDimensionalArray<T>(this->firstDimSize, this->secondDimSize);
	this->DoOperation(newMatrix, value, this->firstDimSize, this->secondDimSize, [](T i, T j) { return i * j; });
	return this->DecideWhereToSave(outMatrix, newMatrix, this->firstDimSize, this->secondDimSize);	
}

template<typename T>
MatrixStatus Matrix<T>::Multiply(const Matrix<T>& otherMatrix, Matrix<T>** outMatrix)
{
	MatrixStatus status = this->CheckIfDataExists(otherMatrix);
	if (status != MatrixStatus::Success)
		return status;
	if (this->secondDimSize != otherMatrix.firstDimSize)
		return MatrixStatus::IncorrectSecondDimension;
	size_t newFirstDimension = this->firstDimSize;
	size_t newSecondDimension = otherMatrix.secondDimSize;
	T** newMatrix = AllocateTwoDimensionalArray<T>(newFirstDimension, newSecondDimension);
	for (size_t i = 0; i < this->firstDimSize; i++) {
		for (size_t j = 0; j < otherMatrix.secondDimSize; j++) {
			T tmp = 0;
			for (size_t k = 0; k < this->secondDimSize; k++) {
				tmp += this->ppMatrix[i][k] * otherMatrix.ppMatrix[k][j];
			}
			newMatrix[i][j] = tmp;
		}
	}
	return this->DecideWhereToSave(outMatrix, newMatrix, newFirstDimension, newSecondDimension);
}

template<typename T>
MatrixStatus Matrix<T>::Transposition(Matrix<T>** outMatrix)
{
	if (this->ppMatrix == nullptr)
		return MatrixStatus::NoMatrix;
	size_t newFirstDimension = this->secondDimSize;
	size_t newSecondDimension = this->firstDimSize;
	T** newMatrix = AllocateTwoDimensionalArray<T>(newFirstDimension, newSecondDimension);
	for (size_t i = 0; i < this->firstDimSize; i++) {
		for (size_t j = 0; j < this->secondDimSize; j++) {
			newMatrix[j][i] = this->ppMatrix[i][j];
		}
	}
	return this->DecideWhereToSave(outMatrix, newMatrix, newFirstDimension, newSecondDimension);
}

template<typename T>
MatrixStatus Matrix<T>::ScalarProduct(const Matrix<T>& otherVector, T* outScalar)
{
	MatrixStatus status = MatrixStatus::Success;
	if (this->ppMatrix == nullptr)
		status |= MatrixStatus::NoMatrix;
	if (outScalar == nullptr)
		status |= MatrixStatus::NoDataProvided;
	if (status != MatrixStatus::Success)
		return status;
	if (this->firstDimSize != VECTORCOLUMNSIZE || otherVector.firstDimSize != VECTORCOLUMNSIZE)
		status |= MatrixStatus::IncorrectFirstDimension;
	if (this->secondDimSize != otherVector.secondDimSize)
		status |= MatrixStatus::IncorrectSecondDimension;
	if (status != MatrixStatus::Success)
		return status;
	for (int i = 0; i < this->secondDimSize; i++) {
		*outScalar += this->ppMatrix[0][i] * otherVector.ppMatrix[0][i];
	}
	return MatrixStatus::Success;
}
template<>
inline MatrixStatus Matrix<int>::GenerateRandomValues(size_t range, int startValue)
{
	return this->GenerateRandomValues(range, startValue, [](size_t range, int startValue) { return (int)(std::rand() % range + startValue); });
}
template<>
inline MatrixStatus Matrix<float>::GenerateRandomValues(size_t range, int startValue)
{
	return this->GenerateRandomValues(range, startValue, [](size_t range, int startValue) { return (float)std::rand() / (RAND_MAX / range) + startValue; });
}
template<>
inline MatrixStatus Matrix<double>::GenerateRandomValues(size_t range, int startValue)
{
	return this->GenerateRandomValues(range, startValue, [](size_t range, int startValue) { return (double)std::rand() / (RAND_MAX / range) + startValue; });
}
template<typename T>
MatrixStatus Matrix<T>::GenerateRandomValues(size_t range, int startValue)
{
	return this->GenerateRandomValues(range, startValue, [](size_t range, int startValue) { return T(); });
}


template<typename T>
MatrixStatus Matrix<T>::GetVectorByRow(size_t firstDimensionIndex, Matrix<T>** outVector)
{
	if (this->ppMatrix == nullptr)
		return MatrixStatus::NoMatrix;
	if (firstDimensionIndex >= this->firstDimSize)
		return MatrixStatus::IncorrectFirstDimension;
	T** newMatrix = AllocateTwoDimensionalArray<T>(VECTORCOLUMNSIZE, this->secondDimSize);
	for (size_t i = 0; i < this->secondDimSize; i++) {
		newMatrix[0][i] = this->ppMatrix[firstDimensionIndex][i];
	}
	this->DecideWhereToSave(outVector, newMatrix, VECTORCOLUMNSIZE, this->secondDimSize);
	return MatrixStatus::Success;
}

template<typename T>
MatrixStatus Matrix<T>::GetVectorByColumn(size_t secondDimensionIndex, Matrix<T>** outVector)
{
	if (this->ppMatrix == nullptr)
		return MatrixStatus::NoMatrix;
	if (secondDimensionIndex >= this->secondDimSize)
		return MatrixStatus::IncorrectSecondDimension;
	T** newMatrix = AllocateTwoDimensionalArray<T>(VECTORCOLUMNSIZE, this->firstDimSize);
	for (size_t i = 0; i < this->firstDimSize; i++) {
		newMatrix[0][i] = this->ppMatrix[i][secondDimensionIndex];
	}
	this->DecideWhereToSave(outVector, newMatrix, VECTORCOLUMNSIZE, this->firstDimSize);
	return MatrixStatus::Success;
}

template<typename T>
const T* Matrix<T>::GetValueAtPosition(size_t firstDimIndex, size_t secondDimIndex) const
{
	if (this->ppMatrix == nullptr)
		return nullptr;
	if (firstDimIndex >= this->firstDimSize)
		return nullptr;
	if (secondDimIndex >= this->secondDimSize)
		return nullptr;
	return &this->ppMatrix[firstDimIndex][secondDimIndex];
}

//-------------------------------------------------------------------------------------------------SET--------------------------------------------------------------------------------------------------------------
template<>
inline std::string Matrix<int>::ToString() const
{
	return std::move(this->ToString(DEFAULT_FORMAT_INT, BUFFER_SIZE));
}
template<>
inline  std::string Matrix<float>::ToString() const
{
	return std::move(this->ToString(DEFAULT_FORMAT_FLOAT_AND_DOUBLE, BUFFER_SIZE));
}
template<>
inline std::string Matrix<double>::ToString() const
{
	return std::move(this->ToString(DEFAULT_FORMAT_FLOAT_AND_DOUBLE, BUFFER_SIZE));
}
template<typename T>
std::string Matrix<T>::ToString() const
{
	return std::move(this->ToString(DEFAULT_FORMAT_TYPE_T, BUFFER_SIZE));
}
template<typename T>
std::string Matrix<T>::ToString(const std::string& format, const int bufferSize) const
{
	std::string str = "";
	for (size_t i = 0; i < this->firstDimSize; i++) {
		str += "| ";
		for (size_t j = 0; j < this->secondDimSize; j++) {
			char* buffer = new char[bufferSize];
			std::snprintf(buffer, bufferSize, format.c_str(), this->ppMatrix[i][j]);
			str += buffer;
			delete[] buffer;
			//cout << matrixArr[i][j] << " ";
		}
		str += "|\n";
	}
	str += "\n";
	return std::move(str);
}
template<typename T>
MatrixStatus Matrix<T>::SetNewMatrix(T** newMatrix, size_t firstDimSize, size_t secondDimSize)
{
	if (newMatrix == nullptr)
		return MatrixStatus::NoDataProvided;
	this->RemoveData();
	this->ppMatrix = newMatrix;
	this->firstDimSize = firstDimSize;
	this->secondDimSize = secondDimSize;
	if (this->secondDimSize == VECTORCOLUMNSIZE && this->firstDimSize != this->secondDimSize)
		return this->Transposition();
	return MatrixStatus::Success;
}

template<typename T>
MatrixStatus Matrix<T>::SetNewMatrixFromFile(const std::string& path)
{
	ReadMatrix<T> readMatrix(&path);
	if (readMatrix.ReadFile()) {
		return this->SetNewMatrix(readMatrix.GetMatrix(), readMatrix.GetFirstDimension(), readMatrix.GetSecondDimension());		
	}
	return MatrixStatus::NoDataProvided;
}

template<typename T>
MatrixStatus Matrix<T>::SetValueAtPosition(T& value, size_t firstDimIndex, size_t secondDimIndex)
{
	MatrixStatus status = MatrixStatus::Success;
	if (this->ppMatrix == nullptr)
		return MatrixStatus::NoMatrix;
	if (firstDimIndex >= this->firstDimSize)
		status |= MatrixStatus::IncorrectFirstDimension;
	if (secondDimIndex >= this->secondDimSize)
		status |= MatrixStatus::IncorrectSecondDimension;
	if (status != MatrixStatus::Success)
		return status;
	this->ppMatrix[firstDimIndex][secondDimIndex] = value;
	return MatrixStatus::Success;
}

template<typename T>
MatrixStatus Matrix<T>::SetIdentityMatrix(T& value, T& valueForRest)
{
	if (this->ppMatrix == nullptr)
		return MatrixStatus::NoMatrix;
	if (this->firstDimSize != this->secondDimSize)
		return MatrixStatus::NonSquare;
	for (size_t i = 0; i < this->firstDimSize; i++) {
		this->ppMatrix[i][i] = value;
	}
	for (size_t i = 0; i < this->firstDimSize; i++) {
		for (size_t j = 0; j < this->secondDimSize; j++) {
			if (i != j) {
				this->ppMatrix[i][j] = valueForRest;
			}
		}
	}
	return MatrixStatus::Success;
}

//-------------------------------------------------------------------------------------------OPERATORS--------------------------------------------------------------------------------------------------------------------

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& otherMatrix)
{
	SmartPointer<Matrix<T>> tmp(nullptr);
	MatrixStatus status = this->Add(otherMatrix, tmp);
	if (status != MatrixStatus::Success) {
		throw MatrixException(status);
	}
	return std::move(tmp);
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& otherMatrix)
{
	SmartPointer<Matrix<T>> tmp(nullptr);
	MatrixStatus status = this->Substract(otherMatrix, tmp);
	if (status != MatrixStatus::Success) {
		throw MatrixException(status);
	}
	return std::move(tmp);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T value)
{
	SmartPointer<Matrix<T>> tmp(nullptr);
	MatrixStatus status = this->Multiply(value, tmp);
	if (status != MatrixStatus::Success) {
		throw MatrixException(status);
	}
	return std::move(tmp);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& otherMatrix)
{
	SmartPointer<Matrix<T>> tmp(nullptr);
	MatrixStatus status = this->Multiply(otherMatrix, tmp);
	if (status != MatrixStatus::Success) {
		throw MatrixException(status);
	}
	return std::move(tmp);
}

//=====================================================================================================================================================================================================================
//=====================================================================================================================================================================================================================

template<typename T>
void Matrix<T>::CopyData(const Matrix<T>& otherMatrix)
{
	if (otherMatrix == nullptr)
		return;
	this->RemoveData();
	this->ppMatrix = AllocateTwoDimensionalArray<T>(otherMatrix.firstDimSize, otherMatrix.secondDimSize);
	for (size_t i = 0; i < otherMatrix.firstDimSize; i++) {
		for (size_t j = 0; j < otherMatrix.secondDimSize; j++) {
			this->ppMatrix[i][j] = otherMatrix.ppMatrix[i][j];
		}
	}
	this->firstDimSize = otherMatrix.firstDimSize;
	this->secondDimSize = otherMatrix.secondDimSize;	
}
template<typename T>
void Matrix<T>::MoveData(Matrix<T>& otherMatrix)
{
	if (otherMatrix == nullptr)
		return;
	this->RemoveData();
	this->ppMatrix = otherMatrix.ppMatrix;
	otherMatrix.ppMatrix = nullptr;
	this->firstDimSize = otherMatrix.firstDimSize;
	this->secondDimSize = otherMatrix.secondDimSize;
}

template<typename T>
 void Matrix<T>::RemoveData()
{
	if(this->ppMatrix != nullptr)
		DeallocateTwoDimensionalArray(&this->ppMatrix, this->firstDimSize);
	this->firstDimSize = 0;
	this->secondDimSize = 0;
	this->ppMatrix = nullptr;
}

 template<typename T>
 void Matrix<T>::DoOperation(T** newMatrix, T** secondMatrix, size_t firstDim, size_t secondDim, T (*operation)(T i, T j))
 {
	 for (size_t i = 0; i < firstDim; i++) {
		 for (size_t j = 0; j < secondDim; j++) {
			newMatrix[i][j] = operation(this->ppMatrix[i][j], secondMatrix[i][j]);
		 }
	 }
 }
 template<typename T>
 void Matrix<T>::DoOperation(T** newMatrix, const T& value, size_t firstDim, size_t secondDim, T(*operation)(T i, T j))
 {
	 for (size_t i = 0; i < firstDim; i++) {
		 for (size_t j = 0; j < secondDim; j++) {
			 newMatrix[i][j] = operation(this->ppMatrix[i][j], value);
		 }
	 }
 }
 template<typename T>
 MatrixStatus Matrix<T>::CreateNewMatrix(T*** outMatrix)
 {
	 if (outMatrix == nullptr)
		 return MatrixStatus::NoDataProvided;
	 *outMatrix = AllocateTwoDimensionalArray<T>(this->firstDimSize, this->secondDimSize);
	 if (*outMatrix == nullptr)
		 return MatrixStatus::UnknownError;
	 return MatrixStatus::Success;
 }

 template<typename T>
 MatrixStatus Matrix<T>::CompareData(const Matrix<T>& otherMatrix) const
 {
	 MatrixStatus status = this->CheckIfDataExists(otherMatrix);
	 if (status != MatrixStatus::Success)
		 return status;
	 if (this->firstDimSize != otherMatrix.firstDimSize)
		 status |= MatrixStatus::IncorrectFirstDimension;
	 if (this->secondDimSize != otherMatrix.secondDimSize)
		 status |= MatrixStatus::IncorrectSecondDimension;
	 if (status != MatrixStatus::Success)
		 return status;
	 return MatrixStatus::Success;
 }

 template<typename T>
 MatrixStatus Matrix<T>::CheckIfDataExists() const
 {
	 if (this->ppMatrix == nullptr)
		 return MatrixStatus::NoMatrix;
	 return MatrixStatus::Success;
 }

 template<typename T>
 MatrixStatus Matrix<T>::CheckIfDataExists(const Matrix<T>& otherMatrix) const
 {
	 if (otherMatrix == nullptr || otherMatrix.ppMatrix == nullptr)
		 return MatrixStatus::NoDataProvided;
	 return this->CheckIfDataExists();
 }

 template<typename T>
 MatrixStatus Matrix<T>::CompareAndAllocate(const Matrix<T>& otherMatrix, T*** outMatrix)
 {
	 MatrixStatus status = this->CompareData(otherMatrix);
	 if (status != MatrixStatus::Success)
		 return status;
	 return CreateNewMatrix(outMatrix);
 }

 template<typename T>
 MatrixStatus Matrix<T>::DecideWhereToSave(Matrix<T>** outMatrix, T** newMatrix, size_t firstDimensionSize, size_t secondDimensionSize)
 {
	 if (outMatrix != nullptr) {
		 if (*outMatrix != nullptr) {
			 delete* outMatrix;
		 }
		 *outMatrix = new Matrix<T>(newMatrix, firstDimensionSize, secondDimensionSize);
		 return MatrixStatus::Success;
	 }
	 return this->SetNewMatrix(newMatrix, firstDimensionSize, secondDimensionSize);
 }

 template<typename T>
 MatrixStatus Matrix<T>::GenerateRandomValues(size_t range, int startValue, T(*randSchema)(size_t, int))
 {
	 try {
		 if (this->ppMatrix == nullptr)
			 return MatrixStatus::NoMatrix;
		 for (size_t i = 0; i < this->firstDimSize; i++) {
			 for (size_t j = 0; j < this->secondDimSize; j++) {
				 this->ppMatrix[i][j] = randSchema(range, startValue);
			 }
		 }
		 return MatrixStatus::Success;
	 }
	 catch (std::exception e) {
		 return MatrixStatus::UnknownError;
	 }
 }
