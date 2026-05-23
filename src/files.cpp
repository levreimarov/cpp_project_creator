//
//  files.cpp
//  
//
//  Created by Lev Reimarov on 23.05.2026.
//
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include "flags.hpp"

static void exit_false(const bool value, const int exitcode) {
        if (!value) {
                std::exit(exitcode);
        }
}

void create_gitignore_file(const std::filesystem::path& base) {
                std::ofstream gitignore_file(base / ".gitignore");
                gitignore_file << ".idea\n.vscode\n*.exe\n*.out\n.DS_Store"
                        << "\ncompile_commands.json\nbuild/"
                        << "\nCMakeCache.txt\nCMakeFiles/\nMakefile\ncmake_install.cmake"
                        << std::endl;
                gitignore_file.close();
}
void create_main_file(const std::filesystem::path& base, const Flags& flags) {
                std::ofstream main_cpp_file(base / "src" / "main.cpp");
                exit_false(main_cpp_file.is_open(), EXIT_FAILURE);
                if (!flags.no_main) {
                        main_cpp_file << "#include <iostream>\n\n"
                                      <<"int main(int argc, const char** argv){\n        \n}"<< std::endl;
                }
                main_cpp_file.close();
}
void create_cmake_file(const std::filesystem::path& base, const Flags& flags) {
        std::ofstream cmake_file;
        cmake_file.open(base / "CMakeLists.txt");
        if (!cmake_file.is_open()) {
                std::cerr << "File creation failed\n";
                std::exit(EXIT_FAILURE);
        }
        const std::string name = base.filename().string();
        cmake_file
                << "cmake_minimum_required(VERSION 3.16)\n"
                << "project(" << name << ")\n\n"
                << "set(CMAKE_CXX_STANDARD 20)\n"
                << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
                << "set(CMAKE_CXX_EXTENSIONS OFF)\n\n";

        if (flags.library) {
                cmake_file
                        << "add_library(" << name << "\n"
                        << (flags.is_static ?"STATIC":"SHARED") << "        src/" << name << ".cpp\n"
                        << ")\n\n"
                        << "target_include_directories(" << name << "\n"
                        << "        PUBLIC include\n"
                        << ")\n";
        } else {
                cmake_file
                        << "add_executable(" << name << " src/main.cpp)\n";
        }
        cmake_file
                << "\ntarget_compile_options(" << name
                << " PRIVATE\n$<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>\n"
                << "$<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>\n$<$<CXX_COMPILER_ID:MSVC>:/W4>\n)";
        cmake_file.close();
}

void create_files(const std::filesystem::path& base, const Flags& flags) {
        if (!flags.library) {
                create_main_file(base, flags);
        } else {

                std::ofstream hpp_file(base/"include"/ base.filename()
                                        / (base.filename().string() + ".hpp"));
                exit_false(hpp_file.is_open(), EXIT_FAILURE);

                hpp_file << "#pragma once\nnamespace "
                        << base.filename().string()
                        <<" {\n\n}" << std::endl;

                hpp_file.close();

                std::ofstream cpp_file(base/"src"/ (base.filename().string() + ".cpp"));
                exit_false(cpp_file.is_open(), EXIT_FAILURE);

                cpp_file << "#include \""
                        << (base.filename() / (base.filename().string() + ".hpp\"")).string()
                        << std::endl;
                cpp_file.close();
        }
        if (flags.git) {
                create_gitignore_file(base);
        }
        create_cmake_file(base, flags);
}
