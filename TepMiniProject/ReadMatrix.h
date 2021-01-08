#pragma once
#include <fstream>
#include <vector>;
#include <string>
#include <sstream>
#include <exception>
#include "HelperMethods.h"

const char DELIMITER = ' ';

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
	bool ReadFile();

	/// <summary>
	/// Read data from file
	/// </summary>
	/// <param name="path">Path to file</param>
	/// <returns>True if successful</returns>
	bool ReadFile(const std::string* path);

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
bool ReadMatrix<T>::ReadFile()
{
	if (this->path != nullptr) {
		return this->ReadFile(this->path);
	}
	return false;
}

template<typename T>
bool ReadMatrix<T>::ReadFile(const std::string* path)
{
	try {
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
			std::stringstream stringStream(line);
			int i = 0;
			while (std::getline(stringStream, line, DELIMITER) && i < this->secondDimSize) {				
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
