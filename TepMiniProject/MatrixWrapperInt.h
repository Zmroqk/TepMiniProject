#pragma once
#include "MatrixWrapper.h"

class MatrixWrapperInt : public MatrixWrapper {
public:
	inline MatrixWrapperInt() : MatrixWrapper() { this->matrix = nullptr; };
	inline MatrixWrapperInt(ConsoleManagment* cm, size_t firstDimension, size_t secondDimension) : MatrixWrapper(cm, Type::INT) { this->matrix = new Matrix<int>(firstDimension, secondDimension); };
	inline MatrixWrapperInt(ConsoleManagment* cm, Matrix<int>* matrix) : MatrixWrapper(cm, Type::INT) { this->matrix = matrix; };
	MatrixWrapperInt(ConsoleManagment* cm, const string& path);

	inline ~MatrixWrapperInt() { delete this->matrix; };

	virtual MatrixWrapper* Add(const MatrixWrapper* other, MatrixStatus* status) override;
	virtual MatrixWrapper* Substract(const MatrixWrapper* other, MatrixStatus* status) override;
	virtual MatrixWrapper* Multiply(const MatrixWrapper* other, MatrixStatus* status) override;
	virtual MatrixWrapper* Multiply(MatrixStatus* status) override;
	virtual double ScalarProduct(const MatrixWrapper* other, MatrixStatus* status) override;
	virtual MatrixWrapper* Transposition(MatrixStatus* status) override;
	virtual MatrixStatus Modify() override;
	virtual MatrixStatus GenerateRandomValues() override;
	virtual MatrixStatus SetIdentityMatrix() override;
	virtual size_t GetFirstDimension() override;
	virtual size_t GetSecondDimension() override;

	inline virtual string ToString() override { return std::move(this->matrix->ToString()); }
private:
	Matrix<int>* matrix;
};