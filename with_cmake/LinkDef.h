#ifdef __CLING__
// Standard preamble: turn off creation of dictionaries for "everything":
// we then turn it on only for the types we are interested in.
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

// Turn on creation of dictionaries for nested classes (not needed for TwoInts but often part of the preamble)
#pragma link C++ nestedclasses;

// Turn on creation of dictionaries for class TwoInts
#pragma link C++ class TwoInts;
// Alternatively, with a `+` at the end of a class name: (??? what does it do?)
//#pragma link C++ class TwoInts+;
// ...or a `-` at the end of a class name: (??? what does it do?)
//#pragma link C++ class TwoInts-;

#endif // __CLING__
