#pragma once
#include <string>
using namespace std;

namespace localisation{
	const char NEW_LINE = '\n';
	
	const string STRING_CHOOSE_MATRIX = "Wybierz macierz";
	const string STRING_CHOOSE_OPTION = "Wybierz opcje";
	const string STRING_AVAILABLE_OPTIONS = "Dostepne opcje:";
	const string STRING_PAUSE = "Wcisnij klawisz by kontynuowac";

	const string ERROR_NO_MATRIX = "Brak macierzy";
	const string ERROR_NO_DATA_PROVIDED = "Nie podano danych";
	const string ERROR_NON_SQUARE = "Macierz nie jest kwadratowa";
	const string ERROR_INCORRECT_FIRST_DIMENSION = "Niepoprawny pierwszy wymiar";
	const string ERROR_INCORRECT_SECOND_DIMENSION = "Niepoprawny drugi wymiar";
	const string ERROR_UNKNOWN = "Nieznany blad";

	const string STRING_RETURN = "Wroc";
	const string STRING_ASK_FIRST_DIMENSION = "Podaj pierwszy wymiar macierzy";
	const string STRING_ASK_SECOND_DIMENSION = "Podaj drugi wymiar macierzy";

	const string STRING_OPERATION_UNSUPPORTED = "Operacja niewspierana";

	const string STRING_ASK = "Podaj ";
	const string STRING_MATRIX = "Macierz";
	const string STRING_VECTOR = "Wektor";
	const string STRING_FIRST_MATRIX = "Pierwsza macierz";
	const string STRING_FIRST_VECTOR = "Pierwszy wektor";
	const string STRING_SECOND_MATRIX = "Druga macierz";
	const string STRING_SECOND_VECTOR = "Drugi wektor";
	const string STRING_RESULT = "Wynik";

	const string STRING_ASK_NEW_VALUE = "Podaj nowa wartosc";

	namespace main_menu {
		const string WELCOME_MESSAGE = "Witaj w mini projekcie o macierzach!";

		const string ADD_MATRIX = "Dodaj macierz";
		const string SHOW_MATRIX = "Pokaz macierz";
		const string DELETE_MATRIX = "Usun macierz";
		const string DO_OPERAION_MATRIX = "Wykonaj operacje na macierzach";
		const string MODIFY_MATRIX = "Modyfikuj macierz";
		const string END_PROGRAM = "Zakoncz program";
	}

	namespace type_menu {
		const string CHOOSE_OPTION = "Wybierz typ macierzy";

		const string MATRIX_TYPE_INT = "Macierz typu int";
		const string MATRIX_TYPE_FLOAT = "Macierz typu float";
		const string MATRIX_TYPE_DOUBLE = "Macierz typu double";
		const string MATRIX_TYPE_STRING = "Macierz typu string (Eksperymentalne)";
	}

	namespace add_matrix_menu {
		const string CHOOSE_OPTION = "Wybierz typ utworzenia macierzy";

		const string RANDOM = "Losuj";
		const string FROM_FILE = "Z pliku";
		const string IDENTITY = "Jednostkowa";

		const string ASK_RANDOM_RANGE = "Podaj przedzial losowania";
		const string ASK_RANDOM_START = "Podaj wartosc startowa";

		const string ASK_FILE_PATH = "Podaj sciezke do pliku";

		const string ASK_DIAGONAL = "Podaj wartosc dla przekatnej";
		const string ASK_REST = "Podaj wartosc dla reszty";

		const string CANT_CREATE = "Nie mozna utworzyc macierzy jednostkowej na takich wymiarach";

	}

	namespace operation_menu {
		const string ADD = "Dodaj";
		const string SUBSTRACT = "Odejmij";
		const string MULTIPLY = "Pomnoz";
		const string MULTIPLY_BY_VALUE = "Pomnoz prezez wartosc";
		const string TRANSPOSITION = "Transponuj";
		const string SCALAR_PRODUCT = "Iloczyn skalarny";
	}

	namespace modify_menu {
		const string MODIFY = "Modyfikuj";

		const string ASK_COLUMN = "Podaj kolumne do modyfikacji";
		const string ASK_ROW = "Podaj rzad do modyfikacji";
	}
}