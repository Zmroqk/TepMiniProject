#include "ReadMatrix.h"

void ReadMatrix<int>::ProcessVector(std::vector<std::vector<std::string>>& data)
{
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			this->matrix[i][j] = std::atoi(data[i][j].c_str());
		}
	}
}
void ReadMatrix<float>::ProcessVector(std::vector<std::vector<std::string>>& data)
{
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; i < data[i].size(); j++) {
			this->matrix[i][j] = std::stof(data[i][j].c_str());
		}
	}
}
void ReadMatrix<double>::ProcessVector(std::vector<std::vector<std::string>>& data)
{
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; i < data[i].size(); j++) {
			this->matrix[i][j] = std::stod(data[i][j].c_str());
		}
	}
}