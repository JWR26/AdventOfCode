#include "file_parser.h"

std::vector<std::string> aoc::get_lines(const std::string& file_path) {
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


std::vector<std::string> aoc::split_file_by(const std::string& file_path, const char& delimiter) {
	std::ifstream data{ file_path };
	std::vector<std::string> strings;
	std::string line{};
	while (data) {
		std::getline(data, line, delimiter);
		if (!line.empty()) {
			strings.push_back(line);
		}
		line.clear();
	}
	return strings;
}

std::vector<std::vector<char>> aoc::file_to_grid(const std::string& file_path) {
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

std::pair < std::vector<std::vector<char>>, std::vector < std::pair<int, int>>> aoc::to_grid_with_positions(const std::string& file_path, const std::function<bool(char)>& pred) {
	std::ifstream data{ file_path };
	std::vector<std::vector<char>> grid;
	std::vector<std::pair<int, int>> positions;

	int i{}, j{};

	while (data) {
		std::string line{};
		std::getline(data, line, '\n');
		if (line.empty()) {
			continue;
		}
		std::vector<char> row;
		j = 0;
		for (const char& c : line) {
			row.push_back(c);
			if (pred(c)) {
				positions.push_back(std::make_pair(i, j));
			}
			++j;
		}
		++i;
		grid.push_back(row);
	}

	return std::make_pair(grid, positions);
}

std::string aoc::read_to_string(const std::string& file_path) {
	std::ifstream data{ file_path };
	std::ostringstream ss;
	ss << data.rdbuf();
	return ss.str();
}

std::vector<std::vector<std::string>> aoc::get_paragraphs(const std::string& file_path) {
	std::ifstream data{ file_path };
	std::vector<std::vector<std::string>> paragraphs;
	std::vector<std::string> lines;
	std::string line{};
	while (data) {
		std::getline(data, line, '\n');
		if (!line.empty()) {
			lines.push_back(line);
		}
		else {
			paragraphs.push_back(lines);
			lines.clear();
		}
	}
	return paragraphs;
}

