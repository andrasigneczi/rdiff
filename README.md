# rdiff based on Rolling Hash Algorithm

## Implemented rolling hashes
- Polynomial rolling hash
- Cyclic polynomial rolling hash
You can find descriptions about [rolling hash](https://en.wikipedia.org/wiki/Rolling_hash) and [rdiff](https://linux.die.net/man/1/rdiff) at the links.

## Usage
Usage: rdiff [-h]
       rdiff [OPTIONS] signature basis-file signature-file
       rdiff [OPTIONS] delta signature-file new-file delta-file
       rdiff [OPTIONS] patch basis-file delta-file new-file
        Options
           -h           Show this help message
           -v           Trace internal processing
           -vv          Trace internal processing + show some debug information
           -hash 1      Set hash function to Polynomial rolling hash
           -hash 2      Set hash function to Cyclic polynomial rolling hash (default)
                        The hash function is saved in the signature and delta files,
                        '-hash' parameter is ignored during delta and patch processes
           -s           Show performance statistics

## Description
This code was made for C++ code challenge. The program was implemented considering the following aspects:
- the hash functions must be easily modifiable, replaceable, or a new one easily addable,
- the input sources and output targets must be easily modifiable, replaceable, or a new one easably addable,
- new tasks must be easaly addable to the application
- hash functions must be rolling hashes

## Requirements
The code was compiled and tested on Ubuntu 20.04 64 bit only.
- cmake >= 3.4.1
- clang++-10 or g++-10 (c++20 required)
- gtest library for test compilation
- md5sum, diff should be installed if you want to run the tests

## Git clone, compilation, run the tests
- git clone https://github.com/.... rdiff
- cd rdiff
- cmake CmakeLists.txt
- make -j5
- cd tests
- ./runTests

## Files
### Binaries
- _src/rdiff_
- _src/libRdiff.so_
- _tests/runTests_ works if it is started from the _tests_ directory.

### Sources
_src/Interfaces_ directory:
- _ClockInterface.h_ interface for clocks in order to measure the execution time of any part of the code
- _HashGeneratorInterface.h_ interface for hash function implementations
- _HashStorageInterface.h_ interface for loading/saving the hash values defined in the hash generator implementations
- _InputInterface.h_ interface for loading data from any sources
- _OutputInterface.h_ interface for saving output data to any target
- _LoggerInterface.h_ interface for logging implementations

_src/IO_ directory:
- _FileInput.h_, _FileInput.cpp_ implementation of input functions with ifstream
- _FileOutput.h_, _FileOutput.cpp_ implementation of output functions with ofstream
- _FastFileInput.h_, _FastFileInput.cpp_ implementation of input functions with open/read functions + buffer
- _FastFileOutput.h_, _FastFileOutput.cpp_ implementation of input functions with open/write functions + buffer
- _IOFactory.h_, _IOFactory.cpp_ creates the necessary input/output object based on the URI format. It recognises the file:/// URI format only, other protocols are not implemented.

_src_ directory:
- _Parameters.h, Parameters.cpp_ processes the application's parameters
- _CharacterMap.h, CyclicPolinomialRHash.h, CyclicPolinomialRHash.cpp_ implementation of Cyclic Polinomial Rolling Hash derived from HashGeneratorInterface
- _CyclicPolinomialRHashStorage.h, CyclicPolinomialRHashStorage.cpp_ implementation of a storage class derived from HashStorageInterface
- _PolynomialRHash.h_ implementation of Polynomial Rolling Hash derived from HashStorageInterface
- _PolynomialRHashStorage.h_ implementation of a storage class derived from HashStorageInterface
- _CoutLogger.h, CoutLogger.cpp_ standard output logger implementation derived from LoggerInterface
- _ClockDummy.h, ClockReal.h, ClockReal.cpp_ implementations of ClockInterface
- _ClockFactory.h, ClockFactory.cpp_ instantiates the required clock. If -s parameter is given, ClockReal will be created, ClockDummy otherwise.
- _Rdiff.h, Rdiff.cpp_ implementation of the necessary functions for signature/delta/patch tasks.
- _RdiffBuilder.h, RdiffBuilder.cpp_ instantiates an Rdiff object and adds the necessary input, output, hash generator, logger, clock objects depends on the parameters
- _main.cpp_
- _CMakeLists.txt_

_tests_ directory:
- _parameters.cpp_ tests of class Parameters
- _cyclic_polinomial_rhash.cpp_ tests of class CyclicPolinomialRHash
- _fast_file_input.cpp_ tests of class FastFileInput
- _fast_file_output.cpp_ tests of class FastFileOutput
- _polynomial_rhash.cpp_ tests of class PolynomialRHash
- _rdiff.cpp_ tests of the functionality of class Rdiff
- _rdiff_app.cpp_ tests of the rdiff application (binary) based on diff and md5sums of patched files
- _main.cpp_
- _CMakeLists.txt_

tests/test_cases directory:
- _t0-t11_ directories with txt and binary tests cases, pregenerated outputs for comparison purpose

## Todo
- speed optimalization
- complex tests with huge number of files
- Improve logger functionality

## Author
This version of rdiff was written by András Ignéczi.
