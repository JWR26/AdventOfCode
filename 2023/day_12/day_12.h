#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "file_parser.h"

namespace day_12 {

	using Record = std::pair<std::string, std::vector<size_t>>;

	using ConditionRecords = std::vector<Record>;

	using Cache = std::unordered_map<std::string, size_t>;

	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_12\\input.txt" };
	const std::string DAY_NAME{ "--- Day 12: Hot Springs ---\n" };
	
	const char DAMAGED{ '#' };
	const char OPERATIONAL{ '.' };
	const char UNKNOWN{ '?' };


	void print_answers();

	Record split_record(const std::string& record);

	ConditionRecords get_records(const std::vector<std::string> record_list);

	std::string get_id(const std::string::iterator& first, const std::string::iterator& last, const size_t& b, const size_t& c);

	size_t possible_arrangements(std::string::iterator first, std::string::iterator last, const std::vector<size_t>& pattern, size_t index, size_t n, Cache& cache);

	size_t sum_records(const ConditionRecords& records);

	void unfold_record(Record& record);
}
