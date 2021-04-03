#pragma once
#include <fstream>
#include <vector>;
#include <string>
#include <sstream>
#include <exception>
#include <algorithm>
#include "MatrixErrorCodes.h"
#include "HelperMethods.h"

const char DELIMITER = ' ';

const int CHAR_TO_COMMA = (int)'^';
const int CHAR_COMMA = (int)'.';
const int CHAR_SLASH = (int)'/';


const int DELIMITER_BANNED_RANGE_MIN = (int)'0';
const int DELIMITER_BANNED_RANGE_MAX = (int)'9';
const int DELIMITER_BANNED = (int)'.';
const int DELIMITER_BANNED_SECOND = (int)',';
const int DELIMITER_BANNED_THIRD = (int)'-';


template<typename T>
class ReadMatrix {
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	ReadMatrix();

	/// <summary>
	/// Create matrix from data in file under given path
	/// </summary>
	/// <param name="path">Path to file</param>
	ReadMatrix(const std::string* path);
	inline ~ReadMatrix() { this->RemoveData(); }

	/// <summary>
	/// Read data from file
	/// </summary>
	/// <returns>True if successful</returns>
	bool ReadFile(MatrixStatus* errorCode = nullptr);

	/// <summary>
	/// Read data from file
	/// </summary>
	/// <param name="path">Path to file</param>
	/// <returns>True if successful</returns>
	bool ReadFile(const std::string* path, MatrixStatus* errorCode = nullptr);

	/// <summary>
	/// Get matrix data
	/// </summary>
	/// <returns>Matrix array</returns>
	T** GetMatrix() const { return CopyTwoDimensionalArray<T>(this->matrix, this->firstDimSize, this->secondDimSize); }

	/// <summary>
	/// Get first dimension of matrix
	/// </summary>
	/// <returns>Size of first dimension</returns>
	size_t GetFirstDimension() const { return this->firstDimSize; }

	/// <summary>
	/// Get second dimension of matrix
	/// </summary>
	/// <returns>Size of second dimension</returns>
	size_t GetSecondDimension() const { return this->secondDimSize; }

private:
	/// <summary>
	/// Process data from vector
	/// </summary>
	/// <param name="line">vector data</param>
	void ProcessVector(std::vector<std::vector<std::string>>& line);

	/// <summary>
	/// Find delimiter for this line
	/// </summary>
	/// <param name="line">Line to check</param>
	/// <returns>First character that can be used as delimiter</returns>
	char FindDelimiter(std::string& line);

	/// <summary>
	/// Count delimiter occurance
	/// </summary>
	/// <param name="line">Line to check</param>
	/// <param name="delimiter">Delimiter to find</param>
	/// <returns>First character that can be used as delimiter</returns>s
	int CountDelimiter(std::string& line, char delimiter);

	/// <summary>
	/// Remove all data used by this instance
	/// </summary>
	void RemoveData();

	/// <summary>
	/// Path to file
	/// </summary>
	const std::string* path;

	/// <summary>
	/// Stream to file
	/// </summary>
	std::ifstream* fileStream;

	/// <summary>
	/// Matrix data
	/// </summary>
	T** matrix;

	/// <summary>
	/// First dimension of matrix
	/// </summary>
	size_t firstDimSize;

	/// <summary>
	/// Second dimension of matrix
	/// </summary>
	size_t secondDimSize;
};

template<typename T>
ReadMatrix<T>::ReadMatrix()
{
	this->path = nullptr; 
	this->fileStream = nullptr;
	this->matrix = nullptr;
	this->firstDimSize = 0;
	this->secondDimSize = 0;
}

template<typename T>
ReadMatrix<T>::ReadMatrix(const std::string* path)
{
	this->path = path; 
	this->fileStream = nullptr;
	this->matrix = nullptr;
	this->firstDimSize = 0;
	this->secondDimSize = 0;
}

template<typename T>
bool ReadMatrix<T>::ReadFile(MatrixStatus* errorCode)
{
	if (this->path != nullptr) {
		return this->ReadFile(this->path, errorCode);
	}
	return false;
}

template<typename T>
bool ReadMatrix<T>::ReadFile(const std::string* path, MatrixStatus* errorCode)
{
	try {
		int expectedCount = 0;
		if (errorCode != nullptr)
			*errorCode = MatrixStatus::Success;
		this->RemoveData();
		this->fileStream = new std::ifstream(*path, std::ios::in);
		if (!this->fileStream->is_open()) {
			return false;
		}
		this->firstDimSize = 0;
		this->secondDimSize = INT_MAX;
		std::vector<std::vector<std::string>> lines;
		while (!this->fileStream->eof() && this->fileStream->good()) {
			this->firstDimSize++;
			lines.push_back(std::vector<std::string>());
			std::string line;
			std::getline(*this->fileStream, line);			
			int i = 0;
			//std::replace(line.begin(), line.end(), (char)CHAR_TO_COMMA, (char)CHAR_COMMA);		
			char delimiter = FindDelimiter(line);
			std::stringstream stringStream(line);
			int count = CountDelimiter(line, CHAR_SLASH);
			if (expectedCount == 0)
				expectedCount = count;
			if (count != expectedCount) {			
				if (errorCode != nullptr)
					*errorCode = MatrixStatus::IncorrectFirstDimension;
			}
			while (std::getline(stringStream, line, delimiter) && i < this->secondDimSize) {
				lines[lines.size() - 1].push_back(line);
				i++;
			}	
			if (this->firstDimSize == 1)
				this->secondDimSize = i;
			for (int j = i; j < this->secondDimSize; j++) {
				lines[lines.size() - 1].push_back("");
			}
		}
		this->matrix = AllocateTwoDimensionalArray<T>(this->firstDimSize, this->secondDimSize);
		this->ProcessVector(lines);
		return true;
	}
	catch (std::exception e) {
		return false;
	}
}
template<>
inline void ReadMatrix<int>::ProcessVector(std::vector<std::vector<std::string>>& data)
{
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			if (data[i][j] == "")
				this->matrix[i][j] = 0;
			else
				this->matrix[i][j] = std::atoi(data[i][j].c_str());
		}
	}
}
template<>
inline void ReadMatrix<float>::ProcessVector(std::vector<std::vector<std::string>>& data)
{
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			if (data[i][j] == "")
				this->matrix[i][j] = 0;
			else
				this->matrix[i][j] = std::stof(data[i][j].c_str());
		}
	}
}
template<>
inline void ReadMatrix<double>::ProcessVector(std::vector<std::vector<std::string>>& data)
{
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			if (data[i][j] == "")
				this->matrix[i][j] = 0;
			else
				this->matrix[i][j] = std::stod(data[i][j].c_str());
		}
	}
}
template<typename T>
void ReadMatrix<T>::ProcessVector(std::vector<std::vector<std::string>>& data)
{
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			this->matrix[i][j] = T();
		}
	}
}
template<typename T>
inline char ReadMatrix<T>::FindDelimiter(std::string& line)
{
	int index = 0;
	while (index < line.length() && 
		line[index] >= DELIMITER_BANNED_RANGE_MIN && 
		line[index] <= DELIMITER_BANNED_RANGE_MAX || 
		line[index] == DELIMITER_BANNED || 
		line[index] == DELIMITER_BANNED_SECOND ||
		line[index] == DELIMITER_BANNED_THIRD
		)
	{
		index++;
	}
	if (index < line.length())
		return line[index];
	else
		return DELIMITER;
}
template<typename T>
inline int ReadMatrix<T>::CountDelimiter(std::string& line, char delimiter)
{
	int index = 0;
	int count = 0;
	while (index < line.length())
	{
		if (delimiter == line[index] /* ewentualnie jako drugi warunek && line[index-1] != delimiter */)
			count++;
		index++;
	}
	return count;
}
template<typename T>
void ReadMatrix<T>::RemoveData()
{
	if (fileStream != nullptr) {
		if (fileStream->is_open()) {
			fileStream->close();
		}
		delete fileStream;
	}
	if (this->matrix != nullptr) {
		DeallocateTwoDimensionalArray(&this->matrix, this->firstDimSize);
		this->firstDimSize = 0;
		this->secondDimSize = 0;
	}
}
