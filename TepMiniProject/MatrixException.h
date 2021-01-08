#pragma once
#include <exception>
#include <string>
#include "MatrixErrorCodes.h"

using namespace std;

const string MATRIX_EXCEPTION_ERROR = "Matrix operation error";

class MatrixException : public exception {
public:
	inline MatrixException() { status = MatrixStatus::UnknownError; }
	inline MatrixException(MatrixStatus status) { this->status = status; }
	inline const char* what() const noexcept { return MATRIX_EXCEPTION_ERROR.c_str(); }
	inline MatrixStatus GetMatrixStatus() const noexcept { return this->status; }
private:
	MatrixStatus status;
};