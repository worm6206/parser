C++ SQL Parser for Hyrise Modified
==================================

This is a C++ parser for Hyrise. The parser has been modified from [Original C++ Parser](https://github.com/hyrise/sql-parser) to generate a JSON-like formatted text file which tokenizes an abstract syntax tree which resulted from an input SQL query.

This work is compatibile with OSX and Linux.
This is a C++ parser for Hyrise. We modify it, want it to generate a txt file that tokenizes the input query. This runs on OSX and Linux.

### Links

[Original](https://github.com/hyrise/sql-parser)


### General Usage

**Prerequisites:**
* [bison](https://www.gnu.org/software/bison/) (tested with v3.0.4) (`brew` doesn't install bison properly. Please install manually)
* [flex](http://flex.sourceforge.net/) (tested with v2.5.5)
* [libconfig](https://github.com/hyperrealm/libconfig/tree/master/lib) (can install with `brew install libconfig`)

run following code under folder `src`
```
./example.sh
```

### Credit

Code is based on the C++ Hyrise parser.
