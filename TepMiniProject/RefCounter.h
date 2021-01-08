#pragma once
class RefCounter
{
public:
	inline RefCounter() { count = 0; }
	inline int Add() { return(++count); }
	inline int Dec() { return(--count); };
	inline int Get() { return(count); }
private:
	int count;
};