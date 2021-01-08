#include "MatrixErrorCodes.h"

MatrixStatus operator|(MatrixStatus left, MatrixStatus right) {
	return (MatrixStatus)((int)left | (int)right);
}
MatrixStatus operator&(MatrixStatus left, MatrixStatus right) {
	return (MatrixStatus)((int)left & (int)right);
}
MatrixStatus operator~(MatrixStatus status) {
	return (MatrixStatus)((int)~status);
}
void operator|=(MatrixStatus& left, MatrixStatus right) {
	left = left | right;
}
void operator&=(MatrixStatus& left, MatrixStatus right) {
	left = left & right;
}
bool operator==(MatrixStatus left, MatrixStatus right) {
	if ((int)left == 0 && (int)right == 0)
		return true;
	return (int)(left & right) != 0;
}
bool operator!=(MatrixStatus left, MatrixStatus right) {
	return !(left == right);
}