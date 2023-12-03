#pragma once

#include <functional>
#include <iostream>
#include <set>
#include <string>

#include "parser.h"

namespace day_03 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_03\\input.txt" };
	const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_03\\test.txt" };
	const std::string DAY_NAME{ "--- Day 3: Gear Ratios ---" };
	
	void print_answers();
	int part_one(const std::vector<std::vector<int>>& schematic, const std::vector<std::vector<bool>>& adjacency_table);
	int part_two(const std::vector<std::vector<int>>& schema_numbers, std::vector<std::vector<char>>& raw_schema);

	std::vector<std::vector<int>> number_schema(const std::vector<std::vector<char>>& grid);
	std::vector<std::vector<bool>> generate_adjacency_table(const std::vector<std::vector<char>>& grid);
}

