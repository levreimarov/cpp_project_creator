# cpp_project_creator
## A `cargo new` for c++. 
#### It uses *cmake*, and *C++20*.  
> **note**: Other C++ standarts are planned to be added later.  
# Installation:
### for Unix-based:
```bash
git clone "https://github.com/levreimarov/cpp_project_creator.git" -b dev
cd "cpp_project_creator"
g++ -std=c++20 -o cpp_p "src/main.cpp" "src/flags.cpp" "src/files.cpp" -O2 -Wall -Wextra
echo "Runnin sudo(may request your password)."
sudo mv "./cpp_p" "/usr/local/bin/"
```
#### or with Cmake
```
git clone https://github.com/levreimarov/cpp_project_creator.git -b dev
cd cpp_project_creator
cmake -B build
cmake --build build
sudo cmake --install build
```
---
### for Windows:
> **Warning**: if g++ is not installed,
> replace it in the folowing command with any C++ 20 supporting compiler.
```
git clone https://github.com/levreimarov/cpp_project_creator.git -b dev
cd cpp_project_creator
g++ -std=c++20 -o cpp_p.exe "src/main.cpp" "src/flags.cpp" "src/files.cpp"
mkdir C:\bin 2>nul
move cpp_p.exe C:\bin\
setx /M PATH "%PATH%;C:\bin"
```
#### or with Cmake
```
git clone https://github.com/levreimarov/cpp_project_creator.git -b dev
cd cpp_project_creator
cmake -B build
cmake --build build --config Release
cmake --install build --config Release
```

# Usage :

### Command:
> **Warning**: Order is **really important**.  
> Argument parser is **not** designed to handle any edge cases.
```bash
cpp_p <name> [flags]
```

### Flags:
- `-l` or `--lib` to create a project as a library (by default it is an executable).
- `-a` or `--app` to explicitly specify that you want a normal executable. Added only for future extensions.
- `-ng` or `--no_git` to turn off auto git initialisation (initialised by default)
- `-nmf` or `--no_main_fnc` to remove default file contents of main.cpp (off by default).
- This flags work only if the project is a library:
  > **note**: to create a project as a library use `-l` or `--lib`.
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

# Future Options
- header only library support
- stand-alone support
- other C++ standarts support
- CMake configuration support???
