cmake_minimum_required(VERSION 3.9)
project (readwrite_twoints CXX)

# Look for ROOT. As long as an installation is available in the environment, this should succeed.
message(STATUS "Looking for ROOT")
find_package(ROOT REQUIRED COMPONENTS RIO)
message(STATUS "ROOT ${ROOT_VERSION} found at ${ROOT_BINDIR}")

# This cmake function produces a file called twoints_dict.cxx at build time, as if by calling:
# `rootcling twoints_dict.cxx twoints.h LinkDef.h`
ROOT_GENERATE_DICTIONARY(twoints_dict twoints.hpp LINKDEF LinkDef.h)

# Remember to add the dictionary to the list of source files!
add_executable(readwrite_twoints readwrite_twoints.cpp twoints.cpp twoints_dict.cxx)
target_link_libraries(readwrite_twoints ROOT::RIO)

# This ensures that the dictionary is generated before the executable
add_dependencies(readwrite_twoints twoints_dict)
