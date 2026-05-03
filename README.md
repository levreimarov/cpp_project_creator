# cpp_project_creator
## A `cargo new` for c++. 
#### It uses *cmake*, and *C++20*. 
<br> Other C++ standarts are planned to be added later.<br>(At least i guess they will be added... not sure, its already to many features for me).

# Compiling:
Compiling is simple, just run:
```
 gcc -std=c++20 -o cpp_p src/main.cpp
```
# Usage :

### Command:
note: Order is **really important**.<br> Argument parser is **not** designed to handle any edge cases.
```
./cpp_p <name> \[flags\]
```

### Flags:
- `-l` or `--lib` to create a project as a library (default is an executable).
- `-a` or `--app` to explicitly specifie that you want a normal executable. Added only for future extensions.
- `-ng` or `--no_git` to turn of auto git initialisation (on by default)
- `-nmf` or `--no_main_fnc` to remove default file contents of main.cpp (off by default).
- This flags work only if the project is a library:
  - `-st` or `--static` to specifie that a library should be *static* (off by default).
  - `-sh` or `--shared` to specifie that a library should be *shared* (on by default).
- `-nb` or `--no_build` to *remove* the build directory (off by default).
- `-t` or `--tests` to create a directory for tests (off by default).

# Used libraries:
This project uses only standart c++ libraries.

- fstream
- iostream
- string
- filesystem

# Coming... Maybe?
- header only library support
- stand-alone support
- other C++ standarts support
- CMake configuration support???
