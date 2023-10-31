#pragma once

#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace parser {
	
	std::vector<std::string> get_lines(const std::string& file_path) {
		std::ifstream data{ file_path };
		std::vector<std::string> all_lines;

		while (data) {
			std::string line{};
			std::getline(data, line, '\n');

			if (!line.empty()) {
				all_lines.push_back(line);
			}
		}

		return all_lines;
	}
}


