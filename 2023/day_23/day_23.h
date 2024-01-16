#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "file_parser.h"
#include "graph.h"
#include "input_output.h"

namespace day_23 {
	const std::string DAY_NAME{ "--- Day 23: A Long Walk ---" };

	void print_answers();
	aoc::graph<char> build_graph(const std::vector<std::string>& input);
}


