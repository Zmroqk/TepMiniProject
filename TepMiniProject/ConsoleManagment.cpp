#include "ConsoleManagment.h"

ConsoleManagment::~ConsoleManagment()
{
    for (int i = 0; i < matrixInt.size(); i++) {
        delete matrixInt[i];
    }
    for (int i = 0; i < matrixFloat.size(); i++) {
        delete matrixFloat[i];
    }
    for (int i = 0; i < matrixDouble.size(); i++) {
        delete matrixDouble[i];
    }
    for (int i = 0; i < matrixString.size(); i++) {
        delete matrixString[i];
    }
}

void ConsoleManagment::GetInputHelper(int character, std::string& text) const
{
    switch (character) {
        case BACKSPACE:
            if (text.size() > 0) {
                text = text.substr(0, text.size() - 1);
            }
            cout << (char)BACKSPACE << " " << (char)BACKSPACE;
            break;
        case NEW_LINE:
            break;
        default:
            text += (char)character;
            cout << (char)character;
    }
}

string ConsoleManagment::GetLine(const string& prompt, bool useCLS) const
{
    int character = NEW_LINE;
    string text = "";
    if (useCLS)
        ClearScreen();
    cout << prompt << ": ";
    do {
        character = _getch();
        GetInputHelper(character, text);
    } while (character != NEW_LINE);
    cout << endl;
    return text;
}

int ConsoleManagment::GetInt(const string& prompt, bool useCLS) const
{
    return (int)GetFloat(prompt, useCLS);
}

float ConsoleManagment::GetFloat(const string& prompt, bool useCLS) const
{
    int character = NEW_LINE;
    string text = "";
    if (useCLS)
        ClearScreen();
    cout << prompt << ": ";
    do {      
        character = _getch();
        if (text.size() == 0 && character == MINUS) {
            text += (char)character;
            cout << "-";
        }
        else if ((character >= FIRST_NUMBER_INDEX && character <= LAST_NUMBER_INDEX) || character == NEW_LINE || character == BACKSPACE || character == COMMA) {
            GetInputHelper(character, text);
        }

    } while (character != NEW_LINE);
    cout << endl;
    if (text != "" && text != "-") {
        return stof(text.c_str());
    }
    return 0;
}

int ConsoleManagment::GetOption(const string& prompt, vector<string>& options) const
{
    int wybor;
    string propmpt = prompt + localisation::NEW_LINE;
    for (int i = 0; i < options.size(); i++) {
        propmpt += to_string(i + 1) + ". "  + options[i] + localisation::NEW_LINE;
    }
    propmpt += localisation::STRING_CHOOSE_OPTION;
    do {
        ClearScreen();
        
        try {
            wybor = this->GetInt(propmpt) - 1;
        }
        catch (exception e) {
            wybor = -1;
        }
    } while (wybor < 0 || wybor >= options.size());
    return wybor;
}

int ConsoleManagment::GetOption(const string& prompt, initializer_list<string> options) const
{
    vector<string> opt;
    for (int i = 0; i < options.size(); i++) {
        opt.push_back(options.begin()[i]);
    }
    return this->GetOption(prompt, opt);
}

void ConsoleManagment::Pause() const
{
    cout << localisation::STRING_PAUSE << endl;
    int _ = getchar();
}

void ConsoleManagment::UseMenu()
{
    int option = 0;
    while (option != -1) {
        ClearScreen();
        string title = localisation::main_menu::WELCOME_MESSAGE + localisation::NEW_LINE;
        title += localisation::STRING_AVAILABLE_OPTIONS;
        option = GetOption(title, { 
            localisation::main_menu::ADD_MATRIX, 
            localisation::main_menu::SHOW_MATRIX, 
            localisation::main_menu::DELETE_MATRIX, 
            localisation::main_menu::DO_OPERAION_MATRIX,
            localisation::main_menu::MODIFY_MATRIX,
            localisation::main_menu::END_PROGRAM
            });
        switch (option) {
        case 0:
            UseTypeOfMatrixMenu(&ConsoleManagment::UseCreateMatrixMenu);
            break;
        case 1:
            UseTypeOfMatrixMenu(&ConsoleManagment::UseShowMatrixMenu);
            break;
        case 2:
            UseTypeOfMatrixMenu(&ConsoleManagment::UseDeleteMatrixMenu);
            break;
        case 3:
            UseTypeOfMatrixMenu(&ConsoleManagment::UseDoOperationMenu);
            break;
        case 4:
            UseTypeOfMatrixMenu(&ConsoleManagment::UseModifyMatrixMenu);
            break;
        default:
            option = -1;
            break;
        }
    }   
}

void ConsoleManagment::UseTypeOfMatrixMenu(void(ConsoleManagment::*nextMenu)(Type))
{
    ClearScreen();
    string title = localisation::type_menu::CHOOSE_OPTION;
    int option = GetOption(title, { 
        localisation::type_menu::MATRIX_TYPE_INT, 
        localisation::type_menu::MATRIX_TYPE_FLOAT, 
        localisation::type_menu::MATRIX_TYPE_DOUBLE, 
        localisation::type_menu::MATRIX_TYPE_STRING,
        localisation::STRING_RETURN
        });
    switch (option) {
        case 0: case 1: case 2: case 3: 
            (this->*nextMenu)((Type)option);
            break;
        default:
            return;
    }
}

void ConsoleManagment::UseCreateMatrixMenu(Type option)
{
    ClearScreen();
    string title = localisation::add_matrix_menu::CHOOSE_OPTION;
    int optionLocal = GetOption(title, {
        localisation::add_matrix_menu::RANDOM,
        localisation::add_matrix_menu::FROM_FILE,
        localisation::add_matrix_menu::IDENTITY,
        localisation::STRING_RETURN
        });
    if (optionLocal != 1 && optionLocal != 3) {
        ClearScreen();
        //first question
        string prompt = localisation::STRING_ASK_FIRST_DIMENSION;
        int firstDimension;
        do {
            firstDimension = GetInt(prompt);
        } while (firstDimension <= 0);

        //second question
        ClearScreen();
        prompt = localisation::STRING_ASK_SECOND_DIMENSION;
        int secondDimension;
        do {
            secondDimension = GetInt(prompt);
        } while (secondDimension <= 0);

        //end question
        if (optionLocal == 0) {
            prompt = localisation::add_matrix_menu::ASK_RANDOM_RANGE;
            int range;
            int startValue;
            do {
                range = GetInt(prompt);
            } while (range <= 0);
            prompt = localisation::add_matrix_menu::ASK_RANDOM_START;
            startValue = GetInt(prompt);
            if (option == Type::INT) {
                matrixInt.push_back(new Matrix<int>(firstDimension, secondDimension));
                ProcessResult(matrixInt[matrixInt.size() - 1]->GenerateRandomValues(range, startValue));
            }
            else if (option == Type::FLOAT) {
                matrixFloat.push_back(new Matrix<float>(firstDimension, secondDimension));
                ProcessResult(matrixFloat[matrixFloat.size() - 1]->GenerateRandomValues(range, startValue));
            }
            else if (option == Type::DOUBLE) {
                matrixDouble.push_back(new Matrix<double>(firstDimension, secondDimension));
                ProcessResult(matrixDouble[matrixDouble.size() - 1]->GenerateRandomValues(range, startValue));
            }
            else if (option == Type::STRING) {
                matrixString.push_back(new Matrix<string>(firstDimension, secondDimension));
                ProcessResult(matrixString[matrixString.size() - 1]->GenerateRandomValues(range, startValue));
            }
        }
        else if (optionLocal == 2) {
            auto tempFunction = [](ConsoleManagment& cm, auto& vec, auto* newMatrix, auto& value, auto& valueForRest) {
                if (newMatrix->GetFirstMatrixDimension() != newMatrix->GetSecondMatrixDimension()) {
                    delete newMatrix;
                    cout << localisation::add_matrix_menu::CANT_CREATE << endl;
                    cm.Pause();
                    return;
                }
                vec.push_back(newMatrix);
                cm.ProcessResult(vec[vec.size() - 1]->SetIdentityMatrix(value, valueForRest));
                return;
            };
            prompt = localisation::add_matrix_menu::ASK_DIAGONAL;
            float value = GetFloat(prompt);
            prompt = localisation::add_matrix_menu::ASK_REST;
            float valueForRest = GetFloat(prompt);
            if (option == Type::INT) {
                Matrix<int>* newMatrix = new Matrix<int>(firstDimension, secondDimension);
                int valueTmp = value;
                int valueForRestTmp = valueForRest;
                tempFunction(*this, matrixInt, newMatrix, valueTmp, valueForRestTmp);
            }
            else if (option == Type::FLOAT) {
                Matrix<float>* newMatrix = new Matrix<float>(firstDimension, secondDimension);
                tempFunction(*this, matrixFloat, newMatrix, value, valueForRest);
            }
            else if (option == Type::DOUBLE) {
                Matrix<double>* newMatrix = new Matrix<double>(firstDimension, secondDimension);
                double valueTmp = value;
                double valueForRestTmp = valueForRest;
                tempFunction(*this, matrixDouble, newMatrix, valueTmp, valueForRestTmp);
            }
            else if (option == Type::STRING) {
                cout << localisation::STRING_OPERATION_UNSUPPORTED << endl;
                Pause();
            }
        }
    }      
    else if (optionLocal == 1) {
        auto tempFunction = [](ConsoleManagment& cm, string& path, auto& vec, auto* newMatrix) {
            if (cm.ProcessResult(newMatrix->SetNewMatrixFromFile(path))) {
                vec.push_back(newMatrix);
            }
            else {
                delete newMatrix;
            }
        };
        string path;
        string prompt = localisation::add_matrix_menu::ASK_FILE_PATH;
        path = GetLine(prompt);
        if (option == Type::INT) {
            Matrix<int>* newMatrix = new Matrix<int>();
            tempFunction(*this, path, matrixInt, newMatrix);
        }
        else if (option == Type::FLOAT) {
            Matrix<float>* newMatrix = new Matrix<float>();
            tempFunction(*this, path, matrixFloat, newMatrix);
        }
        else if (option == Type::DOUBLE) {
            Matrix<double>* newMatrix = new Matrix<double>();
            tempFunction(*this, path, matrixDouble, newMatrix);
        }
        else if (option == Type::STRING) {
            Matrix<string>* newMatrix = new Matrix<string>();
            tempFunction(*this, path, matrixString, newMatrix);
        }
    }    
}

void ConsoleManagment::UseShowMatrixMenu(Type option)
{
    void* matrix = nullptr;
    do {
        matrix = ChooseMatrix(option);
        if (matrix != nullptr) {
            if (option == Type::INT) {
                Matrix<int>* tmp = (Matrix<int>*)matrix;
                cout << tmp->ToString() << endl;
            }
            else if (option == Type::FLOAT) {
                Matrix<float>* tmp = (Matrix<float>*)matrix;
                cout << tmp->ToString() << endl;
            }
            else if (option == Type::DOUBLE) {
                Matrix<double>* tmp = (Matrix<double>*)matrix;
                cout << tmp->ToString() << endl;
            }
            else if (option == Type::STRING) {
                Matrix<string>* tmp = (Matrix<string>*)matrix;
                cout << tmp->ToString() << endl;
            }
            Pause();
        }
    } while (matrix != nullptr);  
}

void ConsoleManagment::UseDeleteMatrixMenu(Type option)
{
    ClearScreen();
    void* matrix = ChooseMatrix(option);
    if (matrix != nullptr) {
        auto tempFunction = [](auto& vec, auto searched) {
            int i = 0;
            while (i < vec.size() && vec[i] != searched) {
                i++;
            }
            delete vec[i];
            vec[i] = nullptr;
            vec.erase(vec.begin() + i);
        };
        if (option == Type::INT) {
            tempFunction(matrixInt, (Matrix<int>*)matrix);
        }
        else if (option == Type::FLOAT) {
            tempFunction(matrixFloat, (Matrix<float>*)matrix);
        }
        else if (option == Type::DOUBLE) {
            tempFunction(matrixDouble, (Matrix<double>*)matrix);
        }
        else if (option == Type::STRING) {
            tempFunction(matrixString, (Matrix<string>*)matrix);
        }
    }
}

void ConsoleManagment::UseDoOperationMenu(Type option)
{
    ClearScreen();
    string title = localisation::STRING_CHOOSE_OPTION;
    int optionLocal = 0;
    while (optionLocal != -1) {
        optionLocal = this->GetOption(title, { 
            localisation::operation_menu::ADD, 
            localisation::operation_menu::SUBSTRACT, 
            localisation::operation_menu::MULTIPLY, 
            localisation::operation_menu::TRANSPOSITION, 
            localisation::operation_menu::SCALAR_PRODUCT,
            localisation::STRING_RETURN
            });
        if (optionLocal < 5) {
            void* matrixOne = ChooseMatrix(option);
            if (matrixOne != nullptr) {
                auto tempPrintFunction = [](ConsoleManagment& cm, auto* matrix, auto* matrixSecond, auto* newMatrix) {
                    cout << localisation::STRING_FIRST_MATRIX << endl;
                    cout << matrix->ToString() << endl;
                    cout << localisation::STRING_SECOND_MATRIX << endl;
                    cout << matrixSecond->ToString() << endl;
                    cout << localisation::STRING_RESULT << endl;
                    cout << newMatrix->ToString() << endl;
                    cm.Pause();
                };
                if (optionLocal == 0) {
                    void* matrixSecond = ChooseMatrix(option, localisation::STRING_ASK + localisation::STRING_SECOND_MATRIX);
                    if (matrixSecond == nullptr)
                        return;
                    auto tempFunction = [](ConsoleManagment& cm, auto& vec, auto* matrix, auto* matrixSecond, auto* newMatrix, auto tempPrintFunction) {
                        if (cm.ProcessResult(matrix->Add(*matrixSecond, &newMatrix))) {
                            vec.push_back(newMatrix);
                            tempPrintFunction(cm, matrix, matrixSecond, newMatrix);
                        }
                    };
                    if (option == Type::INT) {
                        Matrix<int>* newMatrix = nullptr;
                        tempFunction(*this, matrixInt, (Matrix<int>*)matrixOne, (Matrix<int>*)matrixSecond, newMatrix, tempPrintFunction);
                    }
                    else if (option == Type::FLOAT) {
                        Matrix <float>* newMatrix = nullptr;
                        tempFunction(*this, matrixFloat, (Matrix<float>*)matrixOne, (Matrix<float>*)matrixSecond, newMatrix, tempPrintFunction);
                    }
                    else if (option == Type::DOUBLE) {
                        Matrix<double>* newMatrix = nullptr;
                        tempFunction(*this, matrixDouble, (Matrix<double>*)matrixOne, (Matrix<double>*)matrixSecond, newMatrix, tempPrintFunction);
                    }
                    else if (option == Type::STRING) {
                        Matrix<string>* newMatrix = nullptr;
                        tempFunction(*this, matrixString, (Matrix<string>*)matrixOne, (Matrix<string>*)matrixSecond, newMatrix, tempPrintFunction);
                    }
                }
                else if (optionLocal == 1) {
                    void* matrixSecond = ChooseMatrix(option, localisation::STRING_ASK + localisation::STRING_SECOND_MATRIX);
                    if (matrixSecond == nullptr)
                        return;
                    auto tempFunction = [](ConsoleManagment& cm, auto& vec, auto* matrix, auto* matrixSecond, auto* newMatrix, auto tempPrintFunction) {
                        if (cm.ProcessResult(matrix->Substract(*matrixSecond, &newMatrix))) {
                            vec.push_back(newMatrix);
                            tempPrintFunction(cm, matrix, matrixSecond, newMatrix);
                        }
                    };
                    if (option == Type::INT) {
                        Matrix<int>* newMatrix = nullptr;
                        tempFunction(*this, matrixInt, (Matrix<int>*)matrixOne, (Matrix<int>*)matrixSecond, newMatrix, tempPrintFunction);
                    }
                    else if (option == Type::FLOAT) {
                        Matrix <float>* newMatrix = nullptr;
                        tempFunction(*this, matrixFloat, (Matrix<float>*)matrixOne, (Matrix<float>*)matrixSecond, newMatrix, tempPrintFunction);
                    }
                    else if (option == Type::DOUBLE) {
                        Matrix<double>* newMatrix = nullptr;
                        tempFunction(*this, matrixDouble, (Matrix<double>*)matrixOne, (Matrix<double>*)matrixSecond, newMatrix, tempPrintFunction);
                    }
                    else if (option == Type::STRING) {
                        cout << "Operacja niewspierana" << endl;
                        Pause();
                    }
                }
                else if (optionLocal == 2) {
                    void* matrixSecond = ChooseMatrix(option, localisation::STRING_ASK + localisation::STRING_SECOND_MATRIX);
                    if (matrixSecond == nullptr)
                        return;
                    auto tempFunction = [](ConsoleManagment& cm, auto& vec, auto* matrix, auto* matrixSecond, auto* newMatrix, auto tempPrintFunction) {
                        if (cm.ProcessResult(matrix->Multiply(*matrixSecond, &newMatrix))) {
                            vec.push_back(newMatrix);
                            tempPrintFunction(cm, matrix, matrixSecond, newMatrix);
                        }
                    };
                    if (option == Type::INT) {
                        Matrix<int>* newMatrix = nullptr;
                        tempFunction(*this, matrixInt, (Matrix<int>*)matrixOne, (Matrix<int>*)matrixSecond, newMatrix, tempPrintFunction);
                    }
                    else if (option == Type::FLOAT) {
                        Matrix <float>* newMatrix = nullptr;
                        tempFunction(*this, matrixFloat, (Matrix<float>*)matrixOne, (Matrix<float>*)matrixSecond, newMatrix, tempPrintFunction);
                    }
                    else if (option == Type::DOUBLE) {
                        Matrix<double>* newMatrix = nullptr;
                        tempFunction(*this, matrixDouble, (Matrix<double>*)matrixOne, (Matrix<double>*)matrixSecond, newMatrix, tempPrintFunction);
                    }
                    else if (option == Type::STRING) {
                        cout << "Operacja niewspierana" << endl;
                        Pause();
                    }
                }
                else if (optionLocal == 3) {
                    auto tempFunction = [](ConsoleManagment& cm, auto& vec, auto* matrix, auto* newMatrix) {
                        if (cm.ProcessResult(matrix->Transposition(&newMatrix))) {
                            vec.push_back(newMatrix);
                            cout << localisation::STRING_MATRIX << endl;
                            cout << matrix->ToString() << endl;
                            cout << localisation::STRING_RESULT << endl;
                            cout << newMatrix->ToString() << endl;
                            cm.Pause();
                        }
                    };
                    if (option == Type::INT) {
                        Matrix<int>* newMatrix = nullptr;
                        tempFunction(*this, matrixInt, (Matrix<int>*)matrixOne, newMatrix);
                    }
                    else if (option == Type::FLOAT) {
                        Matrix<float>* newMatrix = nullptr;
                        tempFunction(*this, matrixFloat, (Matrix<float>*)matrixOne, newMatrix);
                    }
                    else if (option == Type::DOUBLE) {
                        Matrix<double>* newMatrix = nullptr;
                        tempFunction(*this, matrixDouble, (Matrix<double>*)matrixOne, newMatrix);
                    }
                    else if (option == Type::STRING) {
                        Matrix<string>* newMatrix = nullptr;
                        tempFunction(*this, matrixString, (Matrix<string>*)matrixOne, newMatrix);
                    }
                }
                else if (optionLocal == 4) {
                    void* matrixSecond = ChooseMatrix(option, localisation::STRING_ASK + localisation::STRING_SECOND_MATRIX);
                    if (matrixSecond == nullptr)
                        return;
                    auto tempFunction = [](ConsoleManagment& cm, auto& vec, auto* matrix, auto* matrixSecond, auto* value) {
                        if (cm.ProcessResult(matrix->ScalarProduct(*matrixSecond, value))) {
                            cout << localisation::operation_menu::SCALAR_PRODUCT << *value << endl;
                            cout << localisation::STRING_FIRST_VECTOR << endl;
                            cout << matrix->ToString() << endl;
                            cout << localisation::STRING_SECOND_VECTOR << endl;
                            cout << matrixSecond->ToString() << endl;
                            cout << localisation::STRING_RESULT << endl;
                            cout << *value << endl;
                            cm.Pause();
                        }
                    };
                    if (option == Type::INT) {
                        int* value = new int(0);
                        tempFunction(*this, matrixInt, (Matrix<int>*)matrixOne, (Matrix<int>*)matrixSecond, value);
                        delete value;
                    }
                    else if (option == Type::FLOAT) {
                        float* value = new float(0);
                        tempFunction(*this, matrixFloat, (Matrix<float>*)matrixOne, (Matrix<float>*)matrixSecond, value);
                        delete value;
                    }
                    else if (option == Type::DOUBLE) {
                        double* value = new double();
                        tempFunction(*this, matrixDouble, (Matrix<double>*)matrixOne, (Matrix<double>*)matrixSecond, value);
                        delete value;
                    }
                    else if (option == Type::STRING) {
                        cout << localisation::STRING_OPERATION_UNSUPPORTED << endl;
                        Pause();
                    }
                }
            }          
        }
        else {
            optionLocal = -1;
        }
    }
}

void ConsoleManagment::UseModifyMatrixMenu(Type option)
{
    ClearScreen();
    string title = localisation::STRING_CHOOSE_OPTION;
    int optionLocal = 0;
    while (optionLocal != -1) {
        optionLocal = this->GetOption(title, { 
            localisation::modify_menu::MODIFY, 
            localisation::STRING_RETURN 
            });
        if (optionLocal == 0) {
            void* matrix = ChooseMatrix(option);
            if (matrix != nullptr) {
                auto tempFunction = [](ConsoleManagment& cm, auto* matrix, auto& newValue) {
                    cm.ClearScreen();
                    string prompt = localisation::modify_menu::ASK_ROW;
                    int firstDimension;
                    do {
                        firstDimension = cm.GetInt(prompt) - 1;
                    } while (firstDimension < 0 || firstDimension >= matrix->GetFirstMatrixDimension());
                    cm.ClearScreen();
                    prompt = localisation::modify_menu::ASK_COLUMN;
                    int secondDimension;
                    do {
                        secondDimension = cm.GetInt(prompt) - 1;
                    } while (secondDimension < 0 || secondDimension >= matrix->GetSecondMatrixDimension());
                    matrix->SetValueAtPosition(newValue, firstDimension, secondDimension);
                };
                string prompt = localisation::STRING_ASK_NEW_VALUE;
                float value = GetFloat(prompt);
                if (option == Type::INT) {
                    int valueTmp = value;
                    tempFunction(*this, (Matrix<int>*)matrix, valueTmp);
                }
                else if (option == Type::FLOAT) {
                    tempFunction(*this, (Matrix<float>*)matrix, value);
                }
                else if (option == Type::DOUBLE) {
                    double valueTmp = value;
                    tempFunction(*this, (Matrix<double>*)matrix, valueTmp);
                }
                else if (option == Type::STRING) {
                    string valueTmp = to_string(value);
                    tempFunction(*this, (Matrix<string>*)matrix, valueTmp);
                }
            }            
        }
        else {
            optionLocal = -1;
        }
    }
}

void* ConsoleManagment::ChooseMatrix(Type option, const string& prompt)
{
    ClearScreen();
    auto tempFunction = [](ConsoleManagment& cm, auto& vec, const string& prompt) {  //GENERIC LAMBDA EXPRESSION wymaga u¿ycia auto
        vector<string> matrixes;
        for (int i = 0; i < vec.size(); i++) {
            int first = vec[i]->GetFirstMatrixDimension();
            int second = vec[i]->GetSecondMatrixDimension();
            matrixes.push_back("[" + to_string(first) + ", " + to_string(second) + "]");
        }
        matrixes.push_back(localisation::STRING_RETURN);
        int selected = cm.GetOption(prompt, matrixes);
        void* x = nullptr;
        if (selected >= vec.size()) {
            return x;
        }        
        x = (void*)vec[selected];
        return x;
    };
    if (option == Type::INT && matrixInt.size() > 0) {
        return tempFunction(*this, matrixInt, prompt);
    }
    else if (option == Type::FLOAT && matrixFloat.size() > 0) {
        return tempFunction(*this, matrixFloat, prompt);
    }
    else if (option == Type::DOUBLE && matrixDouble.size() > 0) {
        return tempFunction(*this, matrixDouble, prompt);
    }
    else if (option == Type::STRING && matrixString.size() > 0) {
        return tempFunction(*this, matrixString, prompt);
    }
    return nullptr;
}

bool ConsoleManagment::ProcessResult(MatrixStatus status)
{
    if (status == MatrixStatus::IncorrectFirstDimension) {
        cout << localisation::ERROR_INCORRECT_FIRST_DIMENSION << endl;
    }
    if (status == MatrixStatus::IncorrectSecondDimension) {
        cout << localisation::ERROR_INCORRECT_SECOND_DIMENSION << endl;
    }
    if (status == MatrixStatus::NoDataProvided) {
        cout << localisation::ERROR_NO_DATA_PROVIDED  << endl;
    }
    if (status == MatrixStatus::NoMatrix) {
        cout << localisation::ERROR_NO_MATRIX << endl;
    }
    if (status == MatrixStatus::NonSquare) {
        cout << localisation::ERROR_NON_SQUARE << endl;
    }
    if (status == MatrixStatus::UnknownError) {
        cout << localisation::ERROR_UNKNOWN << endl;
    }
    if (status != MatrixStatus::Success) {
        Pause();
        return false;
    }
    return true;
}


