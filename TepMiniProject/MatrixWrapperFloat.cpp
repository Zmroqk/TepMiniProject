#include "MatrixWrapperFloat.h"

MatrixWrapperFloat::MatrixWrapperFloat(ConsoleManagment* cm, const string& path) : MatrixWrapper(cm, Type::FLOAT)
{
    this->matrix = new Matrix<float>(0, 0);
    cm->ProcessResult(this->matrix->SetNewMatrixFromFile(path));
}

MatrixWrapper* MatrixWrapperFloat::Add(const MatrixWrapper* other, MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetType() == other->GetType()) {
        const MatrixWrapperFloat* otherMatrix = (const MatrixWrapperFloat*)other;
        Matrix<float>* newMatrix = nullptr;
        *status = this->matrix->Add(*otherMatrix->matrix, &newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperFloat(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    *status = MatrixStatus::NoMatrix;
    return nullptr;
}

MatrixWrapper* MatrixWrapperFloat::Substract(const MatrixWrapper* other, MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetType() == other->GetType()) {
        const MatrixWrapperFloat* otherMatrix = (const MatrixWrapperFloat*)other;
        Matrix<float>* newMatrix = nullptr;
        *status = this->matrix->Substract(*otherMatrix->matrix, &newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperFloat(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    *status = MatrixStatus::NoMatrix;
    return nullptr;
}

MatrixWrapper* MatrixWrapperFloat::Multiply(const MatrixWrapper* other, MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetType() == other->GetType()) {
        const MatrixWrapperFloat* otherMatrix = (const MatrixWrapperFloat*)other;
        Matrix<float>* newMatrix = nullptr;
        *status = this->matrix->Multiply(*otherMatrix->matrix, &newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperFloat(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    return nullptr;
}
MatrixWrapper* MatrixWrapperFloat::Multiply(MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetConsoleManagment() != nullptr) {
        Matrix<float>* newMatrix = nullptr;
        float value = this->GetConsoleManagment()->GetFloat("Podaj wartosc przez ktora macierz ma byc pomnozona");
        *status = this->matrix->Multiply(value, &newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperFloat(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    *status = MatrixStatus::NoMatrix;
    return nullptr;
}
double MatrixWrapperFloat::ScalarProduct(const MatrixWrapper* other, MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetType() == other->GetType()) {
        float scalar = 0;
        const MatrixWrapperFloat* otherMatrix = (const MatrixWrapperFloat*)other;
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
MatrixWrapper* MatrixWrapperFloat::Transposition(MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetConsoleManagment() != nullptr) {
        Matrix<float>* newMatrix = nullptr;
        *status = this->matrix->Transposition(&newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperFloat(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    return nullptr;
}
MatrixStatus MatrixWrapperFloat::Modify()
{
    if (this->matrix != nullptr && this->GetConsoleManagment() != nullptr) {
        ConsoleManagment* cm = this->GetConsoleManagment();
        cm->ClearScreen();
        float firstDimension;
        do {
            firstDimension = cm->GetFloat(localisation::modify_menu::ASK_ROW) - 1;
        } while (firstDimension < 0 || firstDimension >= matrix->GetFirstMatrixDimension());
        cm->ClearScreen();
        float secondDimension;
        do {
            secondDimension = cm->GetFloat(localisation::modify_menu::ASK_COLUMN) - 1;
        } while (secondDimension < 0 || secondDimension >= matrix->GetSecondMatrixDimension());
        float value = cm->GetFloat(localisation::STRING_ASK_NEW_VALUE);
        return matrix->SetValueAtPosition(value, firstDimension, secondDimension);
    }
    return MatrixStatus::NoMatrix;
}

MatrixStatus MatrixWrapperFloat::GenerateRandomValues()
{
    ConsoleManagment* cm = this->GetConsoleManagment();
    float range = 0;
    do { range = cm->GetFloat(localisation::add_matrix_menu::ASK_RANDOM_RANGE); } while (range <= 0);
    float startValue = cm->GetFloat(localisation::add_matrix_menu::ASK_RANDOM_START);
    if (this->matrix != nullptr && cm != nullptr) {
        return this->matrix->GenerateRandomValues(range, startValue);
    }
    return MatrixStatus::NoMatrix;
}
MatrixStatus MatrixWrapperFloat::SetIdentityMatrix() //czy matrixWrapper nie powinien mieæ dostêpu do consolemanagment?
{
    if (this->matrix != nullptr || this->GetConsoleManagment() != nullptr) {
        ConsoleManagment* cm = this->GetConsoleManagment();
        float valueTmp = cm->GetFloat(localisation::add_matrix_menu::ASK_DIAGONAL);
        float valueForRestTmp = cm->GetFloat(localisation::add_matrix_menu::ASK_REST);
        return this->matrix->SetIdentityMatrix(valueTmp, valueForRestTmp);
    }
    return MatrixStatus::NoMatrix;
}

size_t MatrixWrapperFloat::GetFirstDimension()
{
    return this->matrix->GetFirstMatrixDimension();
}

size_t MatrixWrapperFloat::GetSecondDimension()
{
    return this->matrix->GetSecondMatrixDimension();
}
