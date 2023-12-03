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

std::vector<std::vector<char>> parser::file_to_grid(const std::string& file_path) {
	std::ifstream data{ file_path };
	std::vector<std::vector<char>> grid;

	while (data) {
		std::string line{};
		std::getline(data, line, '\n');
		if (line.empty()) {
			continue;
		}
		std::vector<char> row;
		for (const char& c : line) {
			row.push_back(c);
		}

		grid.push_back(row);
	}

	return grid;
}

std::string parser::read_to_string(const std::string& file_path) {
	std::ifstream data{ file_path };
	std::ostringstream ss;
	ss << data.rdbuf();
	return ss.str();
}
