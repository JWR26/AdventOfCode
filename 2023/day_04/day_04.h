#pragma once

#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace day_04 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_04\\input.txt" };
	const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_04\\test.txt" };
	const std::string DAY_NAME{ "--- Day 4: Scratchcards ---" };

	std::vector<std::pair<std::set<int>, std::set<int>>> parse_cards(const std::string& file_path);
	void print_answers();
}