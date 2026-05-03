#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

class Flags { // maybe later this will be a struct...
public:
  Flags() = default;
  /* Anyone who reads this
     i know about bit fields, 
     just there are not enough flags!
     even for int8_t. 
     Also not that
     much of an optimization.
  */
  bool git  = 1;
  bool library = 0;
  bool no_build_folder = 0;
  bool no_main = 0;
  bool tests = 0;
  bool is_static = 0;

  Flags(const int argc, const char** argv) {
    for (int i = 1; i< argc; i++) {
      std::string arg = std::string(argv[i]);
      if (arg == "--no_git" || arg == "-ng") {
        this->git = 0;
        continue;
      }
      if (arg == "--no_main_fnc" || arg == "-nmf") {
        this->no_main = 1;
        continue;
      }
      if (arg == "--lib" || arg == "-l") {
        this->library = 1;
        continue;
      }
      if (arg == "--app" || arg == "-a") {
        this->library = 0;
        continue;
      }
      // shared and static controle the same flag.
      if (arg == "--static" || arg == "-st") {
        this->is_static = 1;
        continue;
      }
      if (arg == "--shared" || arg == "-sh") {
        this->is_static = 0;
        continue;
      }
      if (arg == "--no_build"|| arg == "-nb") {
        this->no_build_folder = 1;
      }
      if (arg == "--tests"|| arg == "-t") {
        this->tests = 1;
      }
    }
  }
};
void exit_false(const bool value, const int exitcode) {  
  if (!value) {
    std::exit(exitcode);
  }
}
void create_gitignore_file(const std::filesystem::path& base) {
    std::ofstream gitignore_file(base / ".gitignore");
    gitignore_file <<
      ".idea\n.vscode\n*.exe\n*.out\n.DS_Store\ncompile_commands.json\nbuild/\nCMakeCache.txt\nCMakeFiles/\nMakefile\ncmake_install.cmake"
      << std::endl;
    gitignore_file.close();
}
void create_main_file(const std::filesystem::path& base, const Flags& flags) {
    std::ofstream main_cpp_file(base / "src" / "main.cpp");
    exit_false(main_cpp_file.is_open(), EXIT_FAILURE);
    if (!flags.no_main) {

      main_cpp_file << "#include <iostream>\n\nint main(int argc, const char** argv){\n  \n}"<< std::endl;
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
      << (flags.is_static ?"STATIC":"SHARED") << "  src/" << name << ".cpp\n"
      << ")\n\n"
      << "target_include_directories(" << name << "\n"
      << "  PUBLIC include\n"
      << ")\n";
  } else {
    cmake_file
      << "add_executable(" << name << " src/main.cpp)\n";
  }

  cmake_file.close();
}

void create_files(const std::filesystem::path& base, const Flags& flags) {
  if (!flags.library) {
    create_main_file(base, flags);
  } else {

    std::ofstream hpp_file(base/"include"/ base.filename().string()/(base.filename().string() + ".hpp"));
    exit_false(hpp_file.is_open(), EXIT_FAILURE);

    hpp_file << "#pragma once\nnamespace "<< base.filename().string() <<" {\n\n}" << std::endl;

    hpp_file.close();

    std::ofstream cpp_file(base/"src"/ (base.filename().string() + ".cpp"));
    exit_false(cpp_file.is_open(), EXIT_FAILURE);

    cpp_file << "#include \"" << base.filename().string() << "/" << base.filename().string()<<".hpp\"" << std::endl;
    cpp_file.close();
  }
  if (flags.git) {
    create_gitignore_file(base);
  }
  create_cmake_file(base, flags);
}

void run_git_init(const Flags& flags, const std::filesystem::path& baseDirectory) {
    const std::string cmd = "git init \"" + baseDirectory.string() + "\"";
    std::cout << "Running " << cmd << "." << std::endl;
    system(cmd.c_str());
}

int main(const int argc, const char ** argv) {
  std::cout << "started!" << std::endl;
  const auto flags = Flags(argc, argv);

  if (argc < 2) {
    std::cerr << "Directory name not specified, exiting..." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  const std::filesystem::path baseDirectory = argv[1];

  std::filesystem::create_directories(baseDirectory / "src");
  if (!flags.no_build_folder) {
    std::filesystem::create_directories(baseDirectory / "build");
  }
  if (flags.tests) {
    std::filesystem::create_directories(baseDirectory / "tests");
  }
  if (flags.library) {
    std::filesystem::create_directories(baseDirectory / "include" / baseDirectory.filename());
  }

  std::cout << "Created directories." << std::endl;

  create_files(baseDirectory, flags);
  std::cout << "Created Files." << std::endl;

  if (flags.git) {
    run_git_init(flags, baseDirectory);
  }
  std::cout << "Done, results available in this folder." << std::endl;
  return EXIT_SUCCESS;
}
