C++ SQL Parser for Hyrise Modified
==================================

This is a c++ parser for Hyrise. We modify it, want it to generate a txt file that tokenizes the input query. This runs on OSX and Linux.

### Links

[Original](https://github.com/hyrise/sql-parser)


### General Usage

**Prerequisites:**
* [bison](https://www.gnu.org/software/bison/) (tested with v3.0.4)
* [flex](http://flex.sourceforge.net/) (tested with v2.5.5)

Aside from Original Usage
```
make build
````
```
make test
````
To run our `token`, run `make token` at directory `src`, and the executable will be at `bin`.
Example:
```
./token "SELECT * FROM orders;"
```
a txt file named `sample_query` will be generated

### Credit

We wrote code based on the original, we only own what we've modified.
