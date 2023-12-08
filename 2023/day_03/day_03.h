#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>

#include "file_parser.h"

namespace day_03 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_03\\input.txt" };
	const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_03\\test.txt" };
	const std::string DAY_NAME{ "--- Day 3: Gear Ratios ---" };
	
	void print_answers();
	std::vector<std::vector<int>> number_schema(const std::vector<std::vector<char>>& grid);
}

