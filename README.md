# GNUtility
[![CI](https://github.com/gnu-enjoyer/gnutility/actions/workflows/cmake.yml/badge.svg)](https://github.com/gnu-enjoyer/gnutility/actions/workflows/cmake.yml) [![Gitpod](https://img.shields.io/badge/Contribute%20with-Gitpod-908a85?logo=gitpod)](https://gitpod.io/#https://github.com/gnu-enjoyer/gnutility)

C++20 flat utility library
 
## Features

- Threadsafe logger
- Easily extensible CTest unit testing harness  
- Experimental 'flat pack' static library linkage

## Installation

You can download the latest release as a packed build artefact and include the public header manually, or integrate this repo into your build tree for traditional inclusion. 

CMake integration supports either use case.

Note: use target `gnutility` if transitive linkage is desired.

## Acknowledgements

Until g++ supports C++20 `<format>` the logger uses the famous libfmt (c) Victor Zverovich.

## License 

gnutiliy GNU GPL v3 (c) gnu-enjoyer 2022
