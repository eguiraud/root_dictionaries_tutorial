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


// MORE LinkDef syntax:
// +: new streamer
// nothing: old streamer (no schema evolution)
// -: no streamer generated (User must write their own)
// this applies to classes with a ClassDef.
// without a ClassDef it is a no-op.
// Philippe Canal
// 16:29
// 
// a trailing '!' means "no input operator" (use to generator operator<< for TBuffer).
// 
// //  #pragma link [spec] options=... class classname[+-!]
// 
// (see core/dictgen/src/LinkdefReader.cxx()
//       /*    options=...
//        * possible options:
//        *   nostreamer: set G__NOSTREAMER flag
//        *   noinputoper: set G__NOINPUTOPERATOR flag
//        *   evolution: set G__USEBYTECOUNT flag
//        *   nomap: (ignored by roocling; prevents entry in ROOT's rootmap file)
//        *   stub: (ignored by rootcling was a directly for CINT code generation)
//        *   version(x): sets the version number of the class to x
//        */
