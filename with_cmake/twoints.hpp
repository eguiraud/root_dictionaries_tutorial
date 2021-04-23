#pragma once

class TwoInts {
   int _a;
   int _b;

public:
   TwoInts() {}
   TwoInts(int a, int b) : _a(a), _b(b) {}
   int GetA() const;
   int GetB() const;
   TwoInts& SetA(int a);
   TwoInts& SetB(int b);
};
