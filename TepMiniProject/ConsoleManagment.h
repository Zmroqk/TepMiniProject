#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include "Matrix.h"
#include "Type.h"
#include "Localisation.h"
using namespace std;

const int NEW_LINE = (int)'\r';
const int BACKSPACE = 8;
const int COMMA = (int)'.';
const int MINUS = (int)'-';
const int FIRST_NUMBER_INDEX = (int)'0';
const int LAST_NUMBER_INDEX = (int)'9';

const string CLS = "CLS";

//const string STRING_CHOOSE_MATRIX = "Wybierz macierz";
//const string STRING_CHOOSE_OPTION = "Wybierz opcje";
//const string STRING_PAUSE = "Wcisnij klawisz by kontynuowac";

/*
const string ERROR_NO_MATRIX = "Brak macierzy";
const string ERROR_NO_DATA_PROVIDED = "Nie podano danych";
const string ERROR_NON_SQUARE = "Macierz nie jest kwadratowa";
const string ERROR_INCORRECT_FIRST_DIMENSION = "Niepoprawny pierwszy wymiar";
const string ERROR_INCORRECT_SECOND_DIMENSION = "Niepoprawny drugi wymiar";
const string ERROR_UNKNOWN = "Nieznany blad";
*/


class ConsoleManagment {
public:

	~ConsoleManagment();
	string GetLine(const string& prompt, bool useCLS = true) const;
	int GetInt(const string& prompt, bool useCLS = true) const;
	float GetFloat(const string& prompt, bool useCLS = true) const;
	int GetOption(const string& prompt, vector<string>& options) const;
	int GetOption(const string& prompt, initializer_list<string> options) const;


	void Pause() const;
	inline void ClearScreen() const { system(CLS.c_str()); }
	void UseMenu();
	void UseTypeOfMatrixMenu(void(ConsoleManagment::* nextMenu)(Type));
	void UseCreateMatrixMenu(Type option);
	void UseShowMatrixMenu(Type option);
	void UseDeleteMatrixMenu(Type option);
	void UseDoOperationMenu(Type option);
	void UseModifyMatrixMenu(Type option);

	
private:
	void GetInputHelper(int character, std::string& text) const;
	bool ProcessResult(MatrixStatus status);
	void* ChooseMatrix(Type option, const string& prompt = localisation::STRING_CHOOSE_MATRIX);

	vector<Matrix<int>*> matrixInt;
	vector<Matrix<double>*> matrixDouble;
	vector<Matrix<float>*> matrixFloat;
	vector<Matrix<string>*> matrixString;

	//Maybe we could use some vector<SomeWraper> to keep all matrixes in one vector or use?
};