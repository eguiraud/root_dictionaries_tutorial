## Creating ROOT dictionaries for custom classes

ROOT needs so-called "class dictionaries" to perform I/O of custom user classes.
These are auto-generated C++ source files that must be compiled as part of the application that must perform I/O of a given class.
ROOT ships dictionaries for all of its own classes, but to "teach" ROOT to perform I/O of a your own types you will need to generate a dictionary file.

There are several ways to create ROOT dictionaries:

- the [interactive way](#the-interactive-way), via the ROOT prompt
- the [command line way](#the-command-line-way), via the `rootcling` command
- the [CMake way](#the-cmake-way)

<details>
<summary>All examples assume the following source files are present:</summary>
```cpp
// twoints.hpp
class TwoInts {
   int _a;
   int _b;
public:
   TwoInts() {}
   TwoInts(int a, int b) : _a(a), _b(b) {}
   int GetA() const;
   int GetB() const;
   TwoInts &SetA(int a);
   TwoInts &SetB(int b);
};

// twoints.cpp
#include "twoints.hpp"

int TwoInts::GetA() const { return _a; }
int TwoInts::GetB() const { return _b; }
TwoInts& TwoInts::SetA(int a) { _a = a; return *this; }
TwoInts& TwoInts::SetB(int b) { _b = b; return *this; }
```
</details>

### The interactive way

When you compile code from the ROOT prompt using ACLiC, ROOT automatically creates dictionaries for the types defined in that code:

```cpp
root [0] .L twoints.cpp+ // load twoints.cpp (`.L`) after compiling it into a library (`+`)
Info in <TUnixSystem::ACLiC>: creating shared library /home/blue/Scratchpad/work/root_dictionaries_example/interactively_with_aclic/./twoints_cpp.so
root [1] TwoInts ti(1,2);
root [2] TFile f("f.root", "recreate");
root [3] f.WriteObjectAny(&ti, "TwoInts", "ti");
root [4] TwoInts *ti_read_back = f.Get<TwoInts>("ti");
```

See the example [here](???) for more details.

### The command line way

See the example [here](???).

### The CMake way

See the example [here](???).

### What is this `.pcm` file that gets created next to the dictionaries?

ROOT PCM files contain objects that hold information about the persistified class (name, list of datamember's names, typename, byte offsets of data members).
PCMs need to be stored next to the library that contains the compiled class for ROOT to automatically pick up this information, which is necessary for I/O (??? is this true?).

### What about that `ClassDef` thing I have seen around?

`ClassDef`, `ClassImpl` and similar are pre-processor macros that inject ROOT-specific methods and features into a given class.
These are runtime reflection features such as the `IsA` method which returns a `TClass` representing an object's type (the full list of the features added by `ClassDef` can be found at ???).
You don't need to add `ClassDef` to your class if you don't require these features, but having a `ClassDef` might provide a small I/O performance benefit.
If your type inherits from `TObject` (which is _not_ a requirement), then a `ClassDef` is required: it adds implementations for parts of `TObject`'s abstract interface.
A full list of these macros with explanations is available at ???.

### Are there any restrictions on types serialized, e.g. their layout or behavior?

The most notable limiations are that ROOT does not support I/O of `std::shared_ptr`, `std::optional` and `std::variant`.
These types or classes with data members of this type cannot yet be serialized.
A default constructor (or at least an _I/O constructor_, see ???) is mandatory.
??? Outlined destructor?
??? Multiple inheritance?

### Why do I need to generate dictionaries, can't ROOT just ask cling, the C++ interpreter, this information?

Generating dictionaries is precisely "asking the interpreter" the information required to perform I/O of a given C++ type.
The code inside dictionaries then triggers the registration of a class with ROOT's infrastructure at program initialization time,
so ROOT can "find back" I/O information on the class.
For very simple types, like structs with data members of fundamental types, ROOT can actually perform I/O without dictionaries;
we plan to extend this capability to more types in the future.

### Writing to a TFile vs writing into a TTree

ROOT data is very often stored inside `TTree` objects (which are in turn stored inside ROOT files, often manipulated via the TFile class).
ROOT can store your custom types either directly inside a TFile or as a TTree "branch" (i.e. inside a `TTree`).
To pick one or the other option, think of TFiles as directories and TTrees as databases or datasets: if you want to save a single object to a ROOT file,
you can store it directly in the TFile (e.g. via `TFile::WriteObjectAny`); if you want to store several different values of a given type and
later access all of those values as part of a single dataset/database, then it's probably better to create a `TTree` with the appropriate schema,
add the appropriate entries to it and then save the `TTree` to a file.
