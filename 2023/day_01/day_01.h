#pragma once

#include <iostream>
#include <iterator>
#include <functional>
#include <numeric>
#include <string>
#include <vector>

#include "parser.h"

const std::string input_file{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_01\\input.txt" };
const std::string test_file{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_01\\test.txt" };
const std::string test_file_2{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_01\\test2.txt" };

namespace day_01 {
	void print_answers();
	int part_one(const std::vector<std::string>& input);
	int part_two(const std::vector<std::string>& input);
}
