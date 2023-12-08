#pragma once

#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace file_parser {
	
	std::vector<std::string> get_lines(const std::string& file_path);
	std::vector<std::vector<char>> file_to_grid(const std::string& file_path);
	std::pair < std::vector<std::vector<char>>, std::vector < std::pair<int, int>>> to_grid_with_positions(const std::string& file_path, const std::function<bool(char)>& pred);
	std::string read_to_string(const std::string& file_path);
}


