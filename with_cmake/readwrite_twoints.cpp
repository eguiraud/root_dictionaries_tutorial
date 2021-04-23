// compile with e.g.:
// g++ -o readwrite_twoints readwrite_twoints.cpp $(root-config --libs --cflags) twoints.cpp twoints_dict.cpp

#include "TFile.h"
#include "twoints.hpp"
#include <iostream>

int main() {
  {
    // write the `ti` object to an output file
    TwoInts ti(1, 2);
    TFile out_f("f.root", "recreate");
    out_f.WriteObjectAny(&ti, "TwoInts", "ti");
    std::cout << "Written TwoInts(" << ti.GetA() << ", " << ti.GetB() << ")\n";
  }

  // read back the `ti` object from the file
  TFile in_f("f.root");
  auto *tiptr = in_f.Get<TwoInts>("ti");
  std::cout << "Read TwoInts(" << tiptr->GetA() << ", " << tiptr->GetB() << ")\n";

  return 0;
}
