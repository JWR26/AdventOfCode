#pragma once

#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "file_parser.h"

namespace day_21 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_21\\input.txt" };
	const std::string DAY_NAME{ "--- Day 21: Step Counter ---\n" };

	const char ROCK{ '#' };
	const char START{ 'S' };

	using graph = std::unordered_map<int, std::vector<int>>;

	void print_answers();

	std::pair<graph, int> grid_to_graph(const std::vector<std::vector<char>>& grid);

	std::vector<int> reach_in_steps(const graph& g, const int& start, const int& steps);
}

