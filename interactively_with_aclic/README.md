## Generating dictionaries the interactive way, via ACLiC

First of all, we fire up the ROOT interpreter and tell it to compile `twoints.cpp` into a shared library and load it:

```cpp
root [0] .L twoints.cpp+ // load twoints.cpp (`.L`) after compiling it into a library (`+`)
Info in <TUnixSystem::ACLiC>: creating shared library /home/blue/Scratchpad/work/root_dictionaries_example/interactively_with_aclic/./twoints_cpp.so
```

The following files are created:

```bash
twoints_cpp_ACLiC_dict_rdict.pcm  twoints_cpp.d  twoints_cpp.so
```

The ROOT interpreter now knows about our `TwoInts` custom type, and ROOT knows how to perform I/O operations with it!

```cpp
root [1] TwoInts ti(1,2);
root [2] TFile f("f.root", "recreate");
root [3] f.WriteObjectAny(&ti, "TwoInts", "ti")
(int) 68
```

Alright, we wrote the object to file. `WriteObjectAny` returns the number of bytes written to disk.
Why 68 bytes for just two `int`s?
Because ROOT files are self-descriptive, i.e. not only the data is stored, but also all information required to read it back!
In this case, information about the `TwoInts` type itself.

Now in the same or another session we can retrieve that `TwoInts` object from the `f.root` file.
Here we do it in a new ROOT session:

```cpp
// re-load the TwoInts class. The shared library is _not_ regenerated if the files have not changed.
root [0] .L twoints.cpp+
root [1] TFile f("f.root");
root [2] f.ls()
TFile**		f.root	
 TFile*		f.root	
  KEY: TwoInts	ti;1	object title
root [3] TwoInts* ti = f.Get<TwoInts>("ti");
root [8] ti->GetA()
(int) 1
root [9] ti->GetB()
(int) 2
```
