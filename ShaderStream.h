#pragma once
#include <iostream>
#include <fstream>
#include <string>

class ShaderStream {
public:
	static std::string ReadShaderSource(const char *source) {
		std::string res = "";
		std::ifstream src(source);
		if (!src) {
			std::cout << "File could not be opened" << std::endl;
			return NULL;
		}
		while (!src.eof()) {
			std::string line;
			std::getline(src, line);
			res += line + "\n";
			//std::cout << res << std::endl;
		}
		return res;
	}


};