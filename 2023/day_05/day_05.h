#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <ranges>
#include <map>
#include <vector>


namespace day_05 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_05\\input.txt" };
	const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_05\\test.txt" };
	const std::string DAY_NAME{ "--- Day 5: If You Give A Seed A Fertilizer ---" };

	void print_answers();
	int part_one(const std::string& input_file);
	int part_two(const std::string& input_file);
}
