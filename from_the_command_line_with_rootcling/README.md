## Generating dictionaries from the command line, with `rootcling`

`rootcling` is a command line tool that produces ROOT dictionaries from a list of header files and a `LinkDef.h` file.

The `LinkDef.h` file is a C++ header file that by convention contains only instructions relative to dictionary generation:
that's why all of its content is within a `#ifdef __CLING__`, so that it is only visible to ROOT's C++ interpreter.
Older `LinkDef.h` files might use instead `#ifdef __CINT__`: `cint` is the name of ROOT's previous interpreter, and for
backwards compatibility that spelling still works.

Given the following `LinkDef.h` file:

```cpp
#ifdef __CLING__
#pragma link C++ class TwoInts;
#endif
```

dictionaries for the `TwoInts` class can be generated with the following shell command:

```bash
$ rootcling twoints_dict.cpp twoints.hpp LinkDef.h
```

The `twoints_dict.cpp` source file that is generated this way must be compiled together with the application that
performs I/O of the `TwoInts` type. For this example, this should work:

```bash
$ g++ -o readwrite_twoints readwrite_twoints.cpp $(root-config --libs --cflags) twoints.cpp twoints_dict.cpp
$ ./readwrite_twoints // writes out `f.root` and reads its contents back
Written TwoInts(1, 2)
Read TwoInts(1, 2)
```

The `LinkDef.h` in this directory is a bit more complete and shows a few more features.

### `genreflex`, an alternative front-end for dictionary generation

As an alternative to `rootcling`, the `genreflex` command is also available.
This is a different front-end to the exact same underlying technology.
The main difference between `genreflex` and `rootcling` is that the former takes an XML as input instead of a `LinkDef` file.
See `genreflex --help` for more information.

