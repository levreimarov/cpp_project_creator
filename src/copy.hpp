#ifndef AC03DA75_35C7_4F2F_857A_47A3B93189F2
#define AC03DA75_35C7_4F2F_857A_47A3B93189F2
#include <filesystem>
/*
 * This function copies file template to a file with optional placeholder
 * replacement.
 * returns `EXIT_FAILURE` if failed and `EXIT_SUCCESS` if succeeded
 */
int copy_file(std::filesystem::path, std::filesystem::path, bool, std::filesystem::path);
#endif
