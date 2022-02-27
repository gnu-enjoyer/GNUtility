# GNUtility
C++20 flat utility library
 
# Features

- Threadsafe logger
- Easily extensible CTest unit testing harness  
- Experimental 'flat pack' static library linkage

# Installation

You can download the latest release as a packed build artefact and include the public header manually, or integrate this repo into your build tree for traditional inclusion. 

CMake integration supports either use case.

Note: use exported target `gnutility-deps` if transitive linkage is desired

# Acknowledgements

Until g++ supports C++20 `<format>` the logger uses the famous libfmt (c) Victor Zverovich.

# License 

gnutiliy GNU GPL v3 (c) gnu-enjoyer 2022
