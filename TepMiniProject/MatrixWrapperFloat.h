#pragma once
#include "MatrixWrapper.h"

class MatrixWrapperFloat: public MatrixWrapper {
public:
	inline MatrixWrapperFloat() : MatrixWrapper() { matrix = nullptr; };
	inline MatrixWrapperFloat(ConsoleManagment* cm, size_t firstDimension, size_t secondDimension) : MatrixWrapper(cm, Type::FLOAT) { matrix = new Matrix<float>(firstDimension, secondDimension); };
	inline MatrixWrapperFloat(ConsoleManagment* cm, Matrix<float>* matrix) : MatrixWrapper(cm, Type::FLOAT) { this->matrix = matrix; }
	MatrixWrapperFloat(ConsoleManagment* cm, const string& path);

	inline virtual ~MatrixWrapperFloat() { delete this->matrix; };

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
	Matrix<float>* matrix;

};