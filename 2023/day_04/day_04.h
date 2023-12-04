#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <vector>

namespace day_04 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_04\\input.txt" };
	const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_04\\test.txt" };
	const std::string DAY_NAME{ "--- Day 4: Scratchcards ---" };

	void print_answers();
	int part_two(const std::string& input_file);
}