#include "ConsoleManagment.h"
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
	srand(time(NULL));
	ConsoleManagment cm;
	cm.UseMenu();
	return 0;
}