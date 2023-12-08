#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

#include "file_parser.h"

namespace day_08 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_08\\input.txt" };
	const std::string TEST_FILE_A{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_08\\testa.txt" };
	const std::string TEST_FILE_B{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_08\\testb.txt" };
	const std::string TEST_FILE_C{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_08\\testc.txt" };
	const std::string DAY_NAME{ "--- Day 8: Haunted Wasteland ---" };

	const std::string START{ "AAA" };
	const std::string END{ "ZZZ" };

	std::queue<char> get_instructions(const std::string& str);

	std::map<std::string, std::pair<std::string, std::string>> get_network(const std::vector<std::string>& map);

	size_t count_steps(const std::map<std::string, std::pair<std::string, std::string>>& network, const std::queue<char>& instructions, const std::string& start, const std::function<bool(std::string)>& end_cond);

	size_t count_simultaneous_steps(const std::map<std::string, std::pair<std::string, std::string>>& network, const std::queue<char>& instructions);

	void print_answers(); 
}

