#include "MatrixWrapper.h"

MatrixWrapper* MatrixWrapper::CreateMatrixWrapper(ConsoleManagment* cm, Type type, size_t firstDimension, size_t secondDimension, const string& path)
{
    switch (type) {
    case Type::INT:
        if (path != "")
            return new MatrixWrapperInt(cm, path);
        else
            return new MatrixWrapperInt(cm, firstDimension, secondDimension);
    case Type::DOUBLE:
        if (path != "")
            return new MatrixWrapperDouble(cm, path);
        else
            return new MatrixWrapperDouble(cm, firstDimension, secondDimension);
    case Type::FLOAT:
        if (path != "")
            return new MatrixWrapperFloat(cm, path);
        else
            return new MatrixWrapperFloat(cm, firstDimension, secondDimension);
    case Type::STRING:
        //return new MatrixWrapperInt(firstDimension, secondDimension);
        break;
    }
    return nullptr;
}
