#pragma once
#include "Type.h"

/* There is std::any class in C++ 17 but i decided to create one myself */

/// <summary>
/// 
/// </summary>
class any {
public:
	inline any() { this->data = nullptr; this->type = (Type)0; }
	inline any(Type type, void* data) { this->data = data; this->type = type; }
	inline any(any& otherAny) { this->data = otherAny.data; this->type = otherAny.type; }
private:
	void* data;
	Type type;
};