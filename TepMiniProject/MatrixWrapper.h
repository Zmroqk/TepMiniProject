#pragma once
#include <any>
#include "Matrix.h"
#include "Type.h"
#include "ConsoleManagment.h"

using namespace std;

class ConsoleManagment;

class MatrixWrapper {
public:
	static inline MatrixWrapper* CreateMatrixWrapper(ConsoleManagment* cm, Type type, const string& path) { return CreateMatrixWrapper(cm, type, 0, 0, path); }
	static MatrixWrapper* CreateMatrixWrapper(ConsoleManagment* cm, Type type, size_t firstDimension, size_t secondDimension, const string& path = "");

	MatrixWrapper() { this->cm = nullptr; this->matrixType = Type::None; }
	MatrixWrapper(ConsoleManagment* cm, Type type) { this->cm = cm; this->matrixType = type; }
	~MatrixWrapper() {};

	virtual MatrixWrapper* Add(const MatrixWrapper* other, MatrixStatus* status) = 0;
	virtual MatrixWrapper* Substract(const MatrixWrapper* other, MatrixStatus* status) = 0;
	virtual MatrixWrapper* Multiply(const MatrixWrapper* other, MatrixStatus* status) = 0;
	virtual MatrixWrapper* Multiply(MatrixStatus* status) = 0;
	virtual double ScalarProduct(const MatrixWrapper* other, MatrixStatus* status) = 0;
	virtual MatrixWrapper* Transposition(MatrixStatus* status) = 0;
	virtual MatrixStatus Modify() = 0;
	virtual MatrixStatus GenerateRandomValues() = 0;
	virtual MatrixStatus SetIdentityMatrix() = 0;
	virtual string ToString() = 0;	
	virtual size_t GetFirstDimension() = 0;
	virtual size_t GetSecondDimension() = 0;

	inline Type GetType() const { return matrixType; }	
	inline operator string () { return std::move(ToString()); }
protected:
	inline ConsoleManagment* GetConsoleManagment() const { return cm; }
private:
	Type matrixType;
	ConsoleManagment* cm;
};

#include "MatrixWrapperInt.h"
#include "MatrixWrapperFloat.h"
#include "MatrixWrapperDouble.h"