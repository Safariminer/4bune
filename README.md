# 4bune
Follow-up to 3BUNE

## Dependencies
- GCC (with G++ wrapper)
- dyad.c (gathered automatically with ``prepare.sh``)

## Build instructions
1. Prepare
The ``prepare.sh`` script downloads dependencies and structures them correctly to compile 4bune

2. Build
The ``build.sh`` script calls G++ to compile the bouchot.

## Coding style
### Comments
Multi-line comments made out of multiple single-line comments must cascade;
```cpp
// this is a single line comment

/*
    this is a multi-line comment
*/

  // this is a multi-line comment
 // made out of single-line comments
// look how it cascades

```

### Interfaces
Interfaces should be STL-styled, implementations should use camel caps
```cpp
namespace fourbune{
    namespace http{
        class page{
            //[...]
        };
    }
}

class Index : public fourbune::http::page{

};

```

### Indentation
4-indented, with spaces, and please cut your lines that are more than 80, unless it is for a log message. 