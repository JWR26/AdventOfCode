#include "parser.h"

std::vector<std::string> parser::get_lines(const std::string& file_path) {
	std::ifstream data{ file_path };
	std::vector<std::string> all_lines;
	std::string line{};
	while (data) {
		std::getline(data, line, '\n');
		if (!line.empty()) {
			all_lines.push_back(line);
		}
	}
	return all_lines;
}

std::string parser::read_to_string(const std::string& file_path) {
	std::ifstream data{ file_path };
	std::ostringstream ss;
	ss << data.rdbuf();
	return ss.str();
}