#pragma once

#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace aoc {
	
	std::vector<std::string> get_lines(const std::string& file_path);
	std::vector<std::vector<char>> file_to_grid(const std::string& file_path);
	std::pair < std::vector<std::vector<char>>, std::vector < std::pair<int, int>>> to_grid_with_positions(const std::string& file_path, const std::function<bool(char)>& pred);
	std::string read_to_string(const std::string& file_path);

	std::vector<std::string> split_file_by(const std::string& file_path, const char& delimiter);

	std::vector<std::vector<std::string>> get_paragraphs(const std::string& file_path);

	template<typename T = int>
	std::vector<std::vector<T>> get_lines_as_number_lists(const std::string& file_path) {
		std::ifstream data{ file_path };
		std::vector<std::vector<T>> int_lists;

		std::string line{};
		while (data) {
			std::getline(data, line, '\n');
			std::vector<T> ints;
			if (!line.empty()) {
				bool negative{ false };
				T n{};
				for (const auto& c : line) {
					if (isdigit(c)) {
						n = n * 10 + (c - '0');
					}
					else if (c == '-') {
						negative = true;
					}
					else {
						n = negative ? -n : n;
						ints.emplace_back(n);
						n = 0;
						negative = false;
					}
				}
				if (n != 0) {
					n = negative ? -n : n;
					ints.emplace_back(n);
				}
				int_lists.emplace_back(ints);
			}
		}
		return int_lists;

	}

}


