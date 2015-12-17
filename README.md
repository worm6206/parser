C++ SQL Parser for Hyrise Modified
==================================

This is a C++ parser for Hyrise. The parser has been modified from [Original C++ Parser]https://github.com/hyrise/sql-parser to generate a JSON-like formatted text file which tokenizes an abstract syntax tree which resulted from an input SQL query.

This work is compatibile with OSX and Linux.

### Links

[Original](https://github.com/hyrise/sql-parser)


### General Usage

**Prerequisites:**
* [bison](https://www.gnu.org/software/bison/) (tested with v3.0.4)
* [flex](http://flex.sourceforge.net/) (tested with v2.5.5)
* [libconfig](https://github.com/hyperrealm/libconfig/tree/master/lib) (can install with brew install libconfig)


This work functions as the normal C++ parser for Hyrise does. However, the additional functionality is detailed below.

In order to run the frontend which accepts a SQL query, use the following commands to build the work:
```
make build
````
```
make test
````

To run the `token`, run `make token` at directory `src`, and the executable will be at `bin`.
Example:
```
./token "SELECT * FROM orders;"
```
a text file named `sample_query` will be generated.

This code tokenizes for simple, select queries which scan a table for specific columns or the table as a whole, or 2-way joins.

In order to run the configuration file generater, at the directory `src,` run the following commands: 
```
make all
```
```
make run
```

The `make run` will open up the configuration file that was generated in the vim text editor.
### Credit

Code is based on the C++ Hyrise parser.