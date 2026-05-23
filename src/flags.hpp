#ifndef FLAGS_HPP
#define FLAGS_HPP
class Flags {
public:
        Flags() = default;
        bool git = 1;
        bool library = 0;
        bool no_build_folder = 0;
        bool no_main = 0;
        bool tests = 0;
        bool is_static = 0; // done

        Flags(const int argc, const char** argv);
};
#endif
