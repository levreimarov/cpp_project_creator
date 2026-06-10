#include "copy.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

/*
 * Replaces all ocurences not in strings of `from` in `str` with `to`
 */
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	std::size_t index{};
	bool inString = false;
	while (index < str.size()){
		if (str[index] == '"' || str[index] == '\''){
			inString = !inString;
		}
		if (!inString && str.substr(index).starts_with(from)){
			str.replace(index, from.length(), to);
		}
		index++;
	}
}

int copy_file(std::filesystem::path src, std::filesystem::path dst, bool replace_placeholders, std::filesystem::path base = ""){ // TODO: make a better API
	std::ifstream fSrc(src);
	std::ofstream fDst(dst);
	if (!fSrc.is_open() || !fDst.is_open()){
		return EXIT_FAILURE;
	}
	if (!replace_placeholders){
		fDst << fSrc.rdbuf();
	}else if (base == ""){
		fSrc.close();
		fDst.close();
		return EXIT_FAILURE;
	} else {
		std::stringstream ssTemp;
		ssTemp << fSrc.rdbuf();
		std::string temp = ssTemp.str();
		replaceAll(temp, "$proj", base);
		fSrc.close();
		fDst.close();
	}
	return EXIT_SUCCESS;
}
