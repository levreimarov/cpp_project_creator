#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include "flags.hpp"
#include "files.hpp"



void run_git_init(const std::filesystem::path& baseDirectory) {
                const std::string cmd = "git init \"" + baseDirectory.string() + "\"";
                std::cout << "Running " << cmd << "." << std::endl;
                system(cmd.c_str());
}

int main(const int argc, const char ** argv) {
        std::cout << "started!" << std::endl;
        const Flags flags(argc, argv);

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
                run_git_init(baseDirectory);
        }
        std::cout << "Done, results available in this folder." << std::endl;
        return EXIT_SUCCESS;
}
