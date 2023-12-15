#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <unordered_map>

#include "file_parser.h"

namespace day_13 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_13\\input.txt" };
	const std::string DAY_NAME{ "--- Day 13: Point of Incidence ---\n" };

	const std::unordered_map<char, char> FLIP{
		{'#', '.'},
		{'.', '#'},
	};

	void print_answers();

	int find_reflection_line(std::vector<std::string>::const_iterator first, std::vector<std::string>::const_iterator last);

	std::vector<std::string> transpose(const std::vector<std::string>& rows);

	int reflection_line_score(const std::vector<std::string>& pattern);

	int summarise_notes(const std::vector<std::vector<std::string>>& notes);

	std::string::iterator single_mismatch(std::string& a, std::string& b);

	int find_alternative_reflection_line(std::vector<std::string>& notes);

	int summarise_unsmudged_notes(const std::vector<std::vector<std::string>>& notes);
}

