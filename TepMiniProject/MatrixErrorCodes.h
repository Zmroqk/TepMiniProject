#pragma once
enum class MatrixStatus {
	Success = 0,
	IncorrectFirstDimension = 1,
	IncorrectSecondDimension = 2,
	NonSquare = 4,
	NoDataProvided = 8,
	NoMatrix = 16,
	UnknownError = 32
};

MatrixStatus operator|(MatrixStatus left, MatrixStatus right);
MatrixStatus operator&(MatrixStatus left, MatrixStatus right);
MatrixStatus operator~(MatrixStatus status);
void operator|=(MatrixStatus& left, MatrixStatus right);
void operator&=(MatrixStatus& left, MatrixStatus right);
bool operator==(MatrixStatus left, MatrixStatus right);
bool operator!=(MatrixStatus left, MatrixStatus right);