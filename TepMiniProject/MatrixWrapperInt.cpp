#include "MatrixWrapperInt.h"

MatrixWrapperInt::MatrixWrapperInt(ConsoleManagment* cm, const string& path) : MatrixWrapper(cm, Type::INT)
{
    this->matrix = new Matrix<int>(0, 0);
    cm->ProcessResult(this->matrix->SetNewMatrixFromFile(path));
}

MatrixWrapper* MatrixWrapperInt::Add(const MatrixWrapper* other, MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetType() == other->GetType()) {
        const MatrixWrapperInt* otherMatrix = (const MatrixWrapperInt*)other;
        Matrix<int>* newMatrix = nullptr;
        *status = this->matrix->Add(*otherMatrix->matrix, &newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperInt(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    *status = MatrixStatus::NoMatrix;
    return nullptr;
}

MatrixWrapper* MatrixWrapperInt::Substract(const MatrixWrapper* other, MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetType() == other->GetType()) {
        const MatrixWrapperInt* otherMatrix = (const MatrixWrapperInt*)other;
        Matrix<int>* newMatrix = nullptr;
        *status = this->matrix->Substract(*otherMatrix->matrix, &newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperInt(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    *status = MatrixStatus::NoMatrix;
    return nullptr;
}

MatrixWrapper* MatrixWrapperInt::Multiply(const MatrixWrapper* other, MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetType() == other->GetType()) {
        const MatrixWrapperInt* otherMatrix = (const MatrixWrapperInt*)other;
        Matrix<int>* newMatrix = nullptr;
        *status = this->matrix->Multiply(*otherMatrix->matrix, &newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperInt(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    return nullptr;
}
MatrixWrapper* MatrixWrapperInt::Multiply(MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetConsoleManagment() != nullptr) {
        Matrix<int>* newMatrix = nullptr;
        int value = this->GetConsoleManagment()->GetInt("Podaj wartosc przez ktora macierz ma byc pomnozona");
        *status = this->matrix->Multiply(value, &newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperInt(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    *status = MatrixStatus::NoMatrix;
    return nullptr;
}
double MatrixWrapperInt::ScalarProduct(const MatrixWrapper* other, MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetType() == other->GetType()) {
        int scalar = 0;
        const MatrixWrapperInt* otherMatrix = (const MatrixWrapperInt*)other;
        *status = this->matrix->ScalarProduct(*otherMatrix->matrix, &scalar);
        if (*status != MatrixStatus::Success) {
            return 0;
        }
        return scalar;
    }
    else {
        *status = MatrixStatus::UnknownError;
        return 0;
    }
    return 0;
}
MatrixWrapper* MatrixWrapperInt::Transposition(MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetConsoleManagment() != nullptr) {
        Matrix<int>* newMatrix = nullptr;
        *status = this->matrix->Transposition(&newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperInt(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    return nullptr;
}
MatrixStatus MatrixWrapperInt::Modify()
{
    if (this->matrix != nullptr && this->GetConsoleManagment() != nullptr) {
        ConsoleManagment* cm = this->GetConsoleManagment();
        cm->ClearScreen();
        int firstDimension;
        do {
            firstDimension = cm->GetInt(localisation::modify_menu::ASK_ROW) - 1;
        } while (firstDimension < 0 || firstDimension >= matrix->GetFirstMatrixDimension());
        cm->ClearScreen();
        int secondDimension;
        do {
            secondDimension = cm->GetInt(localisation::modify_menu::ASK_COLUMN) - 1;
        } while (secondDimension < 0 || secondDimension >= matrix->GetSecondMatrixDimension());
        int value = cm->GetInt(localisation::STRING_ASK_NEW_VALUE);
        return matrix->SetValueAtPosition(value, firstDimension, secondDimension);
    }
    return MatrixStatus::NoMatrix;
}

MatrixStatus MatrixWrapperInt::GenerateRandomValues()
{
    ConsoleManagment* cm = this->GetConsoleManagment();
    int range = 0;
    do { range = cm->GetInt(localisation::add_matrix_menu::ASK_RANDOM_RANGE); } while (range <= 0);
    int startValue = cm->GetInt(localisation::add_matrix_menu::ASK_RANDOM_START);
    if (this->matrix != nullptr && cm != nullptr) {
        return this->matrix->GenerateRandomValues(range, startValue);
    }
    return MatrixStatus::NoMatrix;
}
MatrixStatus MatrixWrapperInt::SetIdentityMatrix() //czy matrixWrapper nie powinien mieæ dostêpu do consolemanagment?
{
    if (this->matrix != nullptr || this->GetConsoleManagment() != nullptr) {
        ConsoleManagment* cm = this->GetConsoleManagment();
        int valueTmp = cm->GetInt(localisation::add_matrix_menu::ASK_DIAGONAL);
        int valueForRestTmp = cm->GetInt(localisation::add_matrix_menu::ASK_REST);
        return this->matrix->SetIdentityMatrix(valueTmp, valueForRestTmp);
    }
    return MatrixStatus::NoMatrix;
}

size_t MatrixWrapperInt::GetFirstDimension()
{
    return this->matrix->GetFirstMatrixDimension();
}

size_t MatrixWrapperInt::GetSecondDimension()
{
    return this->matrix->GetSecondMatrixDimension();
}
