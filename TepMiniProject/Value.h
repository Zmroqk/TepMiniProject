#pragma once
#include "Matrix.h"
#include <string>

struct Value{
	enum { INT, FLOAT, DOUBLE, STRING } type;
	union {
		Matrix<int>* intMatrix;
		Matrix<float>* floatMatrix;
		Matrix<double>* doubleMatrix;
		Matrix<std::string>* stringMatrix;
	};
};
