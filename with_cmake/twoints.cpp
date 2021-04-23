#include "twoints.hpp"

int TwoInts::GetA() const { return _a; }
int TwoInts::GetB() const { return _b; }
TwoInts& TwoInts::SetA(int a) { _a = a; return *this; }
TwoInts& TwoInts::SetB(int b) { _b = b; return *this; }
