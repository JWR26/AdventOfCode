#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "file_parser.h"

namespace day_18 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_18\\input.txt" };
	const std::string DAY_NAME{ "--- Day 18: Lavaduct Lagoon ---\n" };

	using vertex = std::pair<int64_t, int64_t>;

	const std::unordered_map<char, vertex> DIRECTION{
		{'U' , std::make_pair<int64_t,int64_t>(0, -1)},
		{'D' , std::make_pair<int64_t,int64_t>(0, 1)},
		{'L' , std::make_pair<int64_t,int64_t>(-1, 0)},
		{'R' , std::make_pair<int64_t,int64_t>(1, 0)},
	};

	const std::unordered_map<char, char> HEX_DIRECTION{
		{'0', 'R'},
		{'1', 'D'},
		{'2', 'L'},
		{'3', 'U'},
	};

	void print_answers();

	std::vector<vertex> get_trench(const std::vector<std::string>& dig_plan);

	std::vector<day_18::vertex> get_hex_trench(const std::vector<std::string>& dig_plan);

	int64_t determinant(const vertex& a, const vertex& b);

	int64_t shoelace(const std::vector<vertex>& vertices);
}
