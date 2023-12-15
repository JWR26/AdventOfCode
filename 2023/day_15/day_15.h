#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <string>
#include <vector>

#include "file_parser.h"

namespace day_15 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_15\\input.txt" };
	const std::string DAY_NAME{ "--- Day 15: Lens Library ---\n" };

	struct lens {
		std::string label;
		int focal_length;

		bool operator==(const lens& other) const {
			return (label == other.label && focal_length == other.focal_length);
		}
	};

	void print_answers();

	int hash_char(const char& c, const int& i);

	int hash_string(const std::string& str);

	int sum_sequence(const std::vector<std::string>& sequence);

	std::map<int, std::list<lens>> fill_boxes(const std::vector<std::string>& sequence);

	int calculate_focal_power(const std::map<int, std::list<lens>>& boxes);
}

