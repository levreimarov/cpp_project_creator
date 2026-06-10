#include <string>
#include "flags.hpp"

Flags::Flags(const int argc, const char** argv) {
        for (int i = 1; i< argc; i++) {
                std::string arg = std::string(argv[i]);
                if ("--no_git" == arg || "-ng" == arg) {
                        this->git = 0;
                        continue;
                }
                if ("--no_main_fnc" == arg || "-nmf" == arg) {
                        this->no_main = 1;
                        continue;
                }
                if ("--lib" == arg || "-l" == arg ) {
                        this->library = 1;
                        continue;
                }
                if ("--app" == arg || "-a" == arg) {
                        this->library = 0;
                        continue;
                }
                if ("--static" == arg || "-st" == arg) {
                        this->is_static = 1;
                        continue;
                }
                if ("--shared" == arg || "-sh" == arg) {
                        this->is_static = 0;
                        continue;
                }
                if ("--no_build" == arg || "-nb" == arg) {
                        this->no_build_folder = 1;
                }
                if ("--tests" == arg || "-t" == arg) {
                        this->tests = 1;
                }
        }
}
