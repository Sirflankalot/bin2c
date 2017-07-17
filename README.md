# bin2c
Simple binary to c converter

# usage

```
bin2c.cpp [-h output_header.hpp] [-o output_source] [-l input_bytes_per_line] [-a array_name filename]... 

-o  output file for the arrays
-h  if a header name is provided, extern declarations
    for all arrays will be put in it
-l  amount of (source) bytes to put on one line (4 output bytes per input byte)
-a  add array
```

# cmake usage

1. Add the bin2c subdirectory in your project `add_subdirectory(/path/to/bin2c)`
2. Include bin2c.cmake in your project `include(/path/to/bin2c/bin2c.cmake)`
3. `bin2c ([LENGTH <source bytes per line>] [OUTPUT file.cpp] [HEADER file.hpp] [ARRAYS "<array_name> /path/to/file"]...)`

# License

All the code within bin2c is licensed under the BSD 3-Clause License. The full text of the license can be found in the license file. 
