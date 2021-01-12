#include "MatrixWrapperDouble.h"

MatrixWrapperDouble::MatrixWrapperDouble(ConsoleManagment* cm, const string& path) : MatrixWrapper(cm, Type::DOUBLE)
{
    this->matrix = new Matrix<double>(0, 0);
    this->matrix->SetNewMatrixFromFile(path);
}

MatrixWrapper* MatrixWrapperDouble::Add(const MatrixWrapper* other, MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetType() == other->GetType()) {
        const MatrixWrapperDouble* otherMatrix = (const MatrixWrapperDouble*)other;
        Matrix<double>* newMatrix = nullptr;
        *status = this->matrix->Add(*otherMatrix->matrix, &newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperDouble(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    *status = MatrixStatus::NoMatrix;
    return nullptr;
}

MatrixWrapper* MatrixWrapperDouble::Substract(const MatrixWrapper* other, MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetType() == other->GetType()) {
        const MatrixWrapperDouble* otherMatrix = (const MatrixWrapperDouble*)other;
        Matrix<double>* newMatrix = nullptr;
        *status = this->matrix->Substract(*otherMatrix->matrix, &newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperDouble(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    *status = MatrixStatus::NoMatrix;
    return nullptr;
}

MatrixWrapper* MatrixWrapperDouble::Multiply(const MatrixWrapper* other, MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetType() == other->GetType()) {
        const MatrixWrapperDouble* otherMatrix = (const MatrixWrapperDouble*)other;
        Matrix<double>* newMatrix = nullptr;
        *status = this->matrix->Multiply(*otherMatrix->matrix, &newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperDouble(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    return nullptr;
}
MatrixWrapper* MatrixWrapperDouble::Multiply(MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetConsoleManagment() != nullptr) {
        Matrix<double>* newMatrix = nullptr;
        double value = this->GetConsoleManagment()->GetDouble("Podaj wartosc przez ktora macierz ma byc pomnozona");
        *status = this->matrix->Multiply(value, &newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperDouble(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    *status = MatrixStatus::NoMatrix;
    return nullptr;
}
double MatrixWrapperDouble::ScalarProduct(const MatrixWrapper* other, MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetType() == other->GetType()) {
        double scalar = 0;
        const MatrixWrapperDouble* otherMatrix = (const MatrixWrapperDouble*)other;
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
MatrixWrapper* MatrixWrapperDouble::Transposition(MatrixStatus* status)
{
    if (this->matrix != nullptr && this->GetConsoleManagment() != nullptr) {
        Matrix<double>* newMatrix = nullptr;
        *status = this->matrix->Transposition(&newMatrix);
        if (*status != MatrixStatus::Success) {
            if (newMatrix != nullptr)
                delete newMatrix;
            return nullptr;
        }
        return new MatrixWrapperDouble(this->GetConsoleManagment(), newMatrix);
    }
    else {
        *status = MatrixStatus::UnknownError;
        return nullptr;
    }
    return nullptr;
}
MatrixStatus MatrixWrapperDouble::Modify()
{
    if (this->matrix != nullptr && this->GetConsoleManagment() != nullptr) {
        ConsoleManagment* cm = this->GetConsoleManagment();
        cm->ClearScreen();
        double firstDimension;
        do {
            firstDimension = cm->GetDouble(localisation::modify_menu::ASK_ROW) - 1;
        } while (firstDimension < 0 || firstDimension >= matrix->GetFirstMatrixDimension());
        cm->ClearScreen();
        double secondDimension;
        do {
            secondDimension = cm->GetDouble(localisation::modify_menu::ASK_COLUMN) - 1;
        } while (secondDimension < 0 || secondDimension >= matrix->GetSecondMatrixDimension());
        double value = cm->GetDouble(localisation::STRING_ASK_NEW_VALUE);
        return matrix->SetValueAtPosition(value, firstDimension, secondDimension);
    }
    return MatrixStatus::NoMatrix;
}

MatrixStatus MatrixWrapperDouble::GenerateRandomValues()
{
    ConsoleManagment* cm = this->GetConsoleManagment();
    double range = 0;
    do { range = cm->GetDouble(localisation::add_matrix_menu::ASK_RANDOM_RANGE); } while (range <= 0);
    double startValue = cm->GetDouble(localisation::add_matrix_menu::ASK_RANDOM_START);
    if (this->matrix != nullptr && cm != nullptr) {
        return this->matrix->GenerateRandomValues(range, startValue);
    }
    return MatrixStatus::NoMatrix;
}
MatrixStatus MatrixWrapperDouble::SetIdentityMatrix() //czy matrixWrapper nie powinien mieæ dostêpu do consolemanagment?
{
    if (this->matrix != nullptr || this->GetConsoleManagment() != nullptr) {
        ConsoleManagment* cm = this->GetConsoleManagment();
        double valueTmp = cm->GetDouble(localisation::add_matrix_menu::ASK_DIAGONAL);
        double valueForRestTmp = cm->GetDouble(localisation::add_matrix_menu::ASK_REST);
        return this->matrix->SetIdentityMatrix(valueTmp, valueForRestTmp);
    }
    return MatrixStatus::NoMatrix;
}

size_t MatrixWrapperDouble::GetFirstDimension()
{
    return this->matrix->GetFirstMatrixDimension();
}

size_t MatrixWrapperDouble::GetSecondDimension()
{
    return this->matrix->GetSecondMatrixDimension();
}
