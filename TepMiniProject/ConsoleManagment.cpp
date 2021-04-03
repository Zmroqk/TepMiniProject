#include "ConsoleManagment.h"

ConsoleManagment::~ConsoleManagment()
{
    for (int i = 0; i < matrixes.size(); i++) {
        delete matrixes[i];
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
    return std::move(text);
}

int ConsoleManagment::GetInt(const string& prompt, bool useCLS) const
{
    return (int)GetDouble(prompt, useCLS);
}

float ConsoleManagment::GetFloat(const string& prompt, bool useCLS) const
{
    return (float)GetDouble(prompt, useCLS);
}

double ConsoleManagment::GetDouble(const string& prompt, bool useCLS) const
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
        return stod(text.c_str());
    }
    return 0;
}

int ConsoleManagment::GetOption(const string& prompt, vector<string>& options, bool useReturn) const
{
    if(useReturn)
        options.push_back(localisation::STRING_RETURN);
    int wybor;
    string promptString = prompt + localisation::NEW_LINE;
    for (int i = 0; i < options.size(); i++) {
        promptString += to_string(i + 1) + ". "  + options[i] + localisation::NEW_LINE;
    }
    promptString += localisation::STRING_CHOOSE_OPTION;
    do {
        ClearScreen();    
        try {
            wybor = this->GetInt(promptString) - 1;
            if (useReturn && wybor == options.size() - 1) {
                return -1;
            }
        }
        catch (exception e) {
            wybor = -1;
        }
    } while (wybor < 0 || wybor >= options.size());
    return wybor;
}

int ConsoleManagment::GetOption(const string& prompt, initializer_list<string> options, bool useReturn) const
{
    vector<string> opt;
    for (int i = 0; i < options.size(); i++) {
        opt.push_back(options.begin()[i]);
    }
    return this->GetOption(prompt, opt, useReturn);
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
            }, false);
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
        localisation::type_menu::MATRIX_TYPE_STRING
        });
    if (option != -1) {
        (this->*nextMenu)((Type)(option+1));
    }
}

void ConsoleManagment::UseCreateMatrixMenu(Type option)
{
    ClearScreen();
    string title = localisation::add_matrix_menu::CHOOSE_OPTION;
    int optionLocal = GetOption(title, {
        localisation::add_matrix_menu::RANDOM,
        localisation::add_matrix_menu::FROM_FILE,
        localisation::add_matrix_menu::IDENTITY
        });
    if (optionLocal == -1) {
        return;
    }
    if (optionLocal != 1) {
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

        MatrixWrapper* matrixWrapper = MatrixWrapper::CreateMatrixWrapper(this, option, firstDimension, secondDimension);
        if (matrixWrapper == nullptr) {
            cout << "Tworzenie macierzy nie powiodlo sie" << endl; // dodac do lokalizacji !!!
            Pause();
            return;
        }
        matrixes.push_back(matrixWrapper);
        //end question
        if (optionLocal == 0) {         
            ProcessResult(matrixWrapper->GenerateRandomValues());
        }
        else if (optionLocal == 2) {
            ProcessResult(matrixWrapper->SetIdentityMatrix());
        }
    }      
    else if (optionLocal == 1) {
        string path;
        string prompt = localisation::add_matrix_menu::ASK_FILE_PATH;
        path = GetLine(prompt);
        MatrixWrapper* matrixWrapper = MatrixWrapper::CreateMatrixWrapper(this, option, path);
        if (matrixWrapper == nullptr) {
            cout << "Tworzenie macierzy nie powiodlo sie" << endl; // dodac do lokalizacji !!!
            Pause();
            return;
        }
        matrixes.push_back(matrixWrapper);
    }    
}

void ConsoleManagment::UseShowMatrixMenu(Type option)
{
    MatrixWrapper* matrix = nullptr;
    do {
        matrix = ChooseMatrix(option);
        if (matrix != nullptr) {
            cout << matrix->ToString() << endl;
            Pause();
        }
    } while (matrix != nullptr);  
}

void ConsoleManagment::UseDeleteMatrixMenu(Type option)
{
    ClearScreen();
    MatrixWrapper* matrix = ChooseMatrix(option);
    if (matrix != nullptr) {
        int i = 0;
        while (i < matrixes.size() && matrixes[i] != matrix) {
            i++;
        }
        delete matrixes[i];
        matrixes[i] = nullptr;
        matrixes.erase(matrixes.begin() + i);
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
            localisation::operation_menu::MULTIPLY_BY_VALUE, 
            localisation::operation_menu::TRANSPOSITION, 
            localisation::operation_menu::SCALAR_PRODUCT
            });
        if (optionLocal != -1) {
            MatrixWrapper* matrixOne = ChooseMatrix(option);
            if (matrixOne != nullptr) {
                MatrixStatus status;
                MatrixWrapper* newMatrix = nullptr;
                if (optionLocal != 3 && optionLocal != 4) {
                    MatrixWrapper* matrixSecond = ChooseMatrix(option, localisation::STRING_ASK + localisation::STRING_SECOND_MATRIX);
                    if (matrixSecond != nullptr) {

                        if (optionLocal == 0) {
                            newMatrix = matrixOne->Add(matrixSecond, &status);
                            if (!ProcessResult(status)) {
                                return;
                            }
                            matrixes.push_back(newMatrix);
                        }
                        else if (optionLocal == 1) {
                            newMatrix = matrixOne->Substract(matrixSecond, &status);
                            if (!ProcessResult(status)) {
                                return;
                            }
                            matrixes.push_back(newMatrix);
                        }
                        else if (optionLocal == 2) {
                            newMatrix = matrixOne->Multiply(matrixSecond, &status);
                            if (!ProcessResult(status)) {
                                return;
                            }
                            matrixes.push_back(newMatrix);
                        }
                        else if (optionLocal == 5) {
                            double scalar = matrixOne->ScalarProduct(matrixSecond, &status);
                            if (!ProcessResult(status)) {
                                return;
                            }
                            cout << localisation::STRING_FIRST_MATRIX << endl;
                            cout << matrixOne->ToString() << endl;
                            cout << localisation::STRING_SECOND_MATRIX << endl;
                            cout << matrixSecond->ToString() << endl;
                            cout << localisation::STRING_RESULT << endl;
                            cout << scalar << endl;
                            Pause();
                            return;
                        }
                        OperationResult(matrixOne, matrixSecond, newMatrix);
                    }
                }
                else if (optionLocal == 3) {
                    newMatrix = matrixOne->Multiply(&status);
                    if (!ProcessResult(status)) {
                        return;
                    }
                    matrixes.push_back(newMatrix);
                    OperationResult(matrixOne, newMatrix);
                }
                else if (optionLocal == 4) {
                    newMatrix = matrixOne->Transposition(&status);
                    if (!ProcessResult(status)) {
                        return;
                    }
                    matrixes.push_back(newMatrix);
                    OperationResult(matrixOne, newMatrix);
                }
            }
        }
    }
}

void ConsoleManagment::OperationResult(MatrixWrapper* matrixOne, MatrixWrapper* matrixSecond, MatrixWrapper* newMatrix)
{
    cout << localisation::STRING_FIRST_MATRIX << endl;
    cout << matrixOne->ToString() << endl;
    cout << localisation::STRING_SECOND_MATRIX << endl;
    cout << matrixSecond->ToString() << endl;
    cout << localisation::STRING_RESULT << endl;
    cout << newMatrix->ToString() << endl;
    Pause();
}

void ConsoleManagment::OperationResult(MatrixWrapper* matrixOne, MatrixWrapper* newMatrix)
{
    cout << localisation::STRING_MATRIX << endl;
    cout << matrixOne->ToString() << endl;
    cout << localisation::STRING_RESULT << endl;
    cout << newMatrix->ToString() << endl;
    Pause();
}

void ConsoleManagment::UseModifyMatrixMenu(Type option)
{
    ClearScreen();
    string title = localisation::STRING_CHOOSE_OPTION;
    int optionLocal = 0;
    while (optionLocal != -1) {
        optionLocal = this->GetOption(title, { 
            localisation::modify_menu::MODIFY
            });
        if (optionLocal == 0) {            
            MatrixWrapper* matrix = ChooseMatrix(option);
            if (matrix != nullptr) {
                MatrixStatus status = matrix->Modify();
                if (!ProcessResult(status)) {
                    return;
                }               
            }            
        }
    }
}

MatrixWrapper* ConsoleManagment::ChooseMatrix(Type option, const string& prompt)
{
    ClearScreen();
    vector<string> matrixesStrings;
    vector<MatrixWrapper*> matrixesData;
    int index = 1;
    for (int i = 0; i < this->matrixes.size(); i++) {
        if (option == this->matrixes[i]->GetType()) {
            size_t first = this->matrixes[i]->GetFirstDimension();
            size_t second = this->matrixes[i]->GetSecondDimension();
            matrixesStrings.push_back("[" + to_string(first) + ", " + to_string(second) + "]");
            matrixesData.push_back(this->matrixes[i]);
        }       
    }
    int selected = GetOption(prompt, matrixesStrings);
    if(selected == -1)
        return nullptr;
    return matrixesData[selected];
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


