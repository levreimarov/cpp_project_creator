//
//  files.hpp
//  
//
//  Created by Lev Reimarov on 23.05.2026.
//
#ifndef FILES_HPP
#define FILES_HPP
#include "flags.hpp"
#include <filesystem>
void create_gitignore_file(const std::filesystem::path& base);
void create_main_file(const std::filesystem::path& base, const Flags& flags);
void create_cmake_file(const std::filesystem::path& base, const Flags& flags);
void create_files(const std::filesystem::path& base, const Flags& flags);
#endif
