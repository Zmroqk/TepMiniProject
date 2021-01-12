#pragma once
#include "MatrixWrapper.h"

class MatrixWrapperDouble: public MatrixWrapper {
public:
	inline MatrixWrapperDouble() : MatrixWrapper() { matrix = nullptr; };
	inline MatrixWrapperDouble(ConsoleManagment* cm, size_t firstDimension, size_t secondDimension) : MatrixWrapper(cm, Type::DOUBLE) { matrix = new Matrix<double>(firstDimension, secondDimension); };
	inline MatrixWrapperDouble(ConsoleManagment* cm, Matrix<double>* matrix) : MatrixWrapper(cm, Type::DOUBLE) { this->matrix = matrix; }
	MatrixWrapperDouble(ConsoleManagment* cm, const string& path);

	inline virtual ~MatrixWrapperDouble() { delete this->matrix; };

	// Odziedziczono za poœrednictwem elementu MatrixWrapper
	virtual MatrixWrapper* Add(const MatrixWrapper* other, MatrixStatus* status) override;
	virtual MatrixWrapper* Substract(const MatrixWrapper* other, MatrixStatus* status) override;
	virtual MatrixWrapper* Multiply(const MatrixWrapper* other, MatrixStatus* status) override;
	virtual MatrixWrapper* Multiply(MatrixStatus* status) override;
	virtual double ScalarProduct(const MatrixWrapper* other, MatrixStatus* status) override;
	virtual MatrixWrapper* Transposition(MatrixStatus* status) override;
	virtual MatrixStatus Modify() override;
	virtual MatrixStatus GenerateRandomValues() override;
	virtual MatrixStatus SetIdentityMatrix() override;
	inline virtual string ToString() override { return std::move(this->matrix->ToString()); }
	virtual size_t GetFirstDimension() override;
	virtual size_t GetSecondDimension() override;

private:
	Matrix<double>* matrix;

};