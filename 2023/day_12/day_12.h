#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "file_parser.h"

namespace day_12 {
	template<typename T = int>
	using Record = std::pair<std::string, std::vector<T>>;
	
	template<typename T = int>
	using ConditionRecords = std::vector<Record<T>>;

	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_12\\input.txt" };
	const std::string DAY_NAME{ "--- Day 12: Hot Springs ---\n" };
	
	const char DAMAGED{ '#' };
	const char OPERATIONAL{ '.' };
	const char UNKNOWN{ '?' };

	void print_answers();

	template<typename T = int>
	Record<T> split_record(const std::string& record) {
		const size_t length{ record.find(' ') };
		std::string springs(record, 0, length);

		std::vector<T> pattern;
		auto it{ record.begin() + length - 1 };
		T n{};

		while (it != record.end()) {
			if (isdigit(*it)) {
				n = n * 10 + (*it - '0');
			}
			else if (n > 0) {
				pattern.push_back(n);
				n = 0;
			}
			++it;
		}
		if (n > 0) {
			pattern.push_back(n);
		}

		return std::make_pair(springs, pattern);
	}

	template< typename T = int>
	ConditionRecords<T> get_records(const std::vector<std::string> record_list) {
		ConditionRecords<T> records;

		for (const std::string& str : record_list) {
			records.push_back(split_record(str));
		}

		return records;
	}

	template<typename T = int>
	T possible_arrangements(std::string::iterator first, std::string::iterator last, std::vector<T> pattern, T index, T n) {
		T arrangements{};

		while (first != last) {
			if (*first == DAMAGED) {
				++n;
				// too many consecutive damaged springs
				if (n > pattern[index]) {
					return 0;
				}
			}

			if (*first == OPERATIONAL && n > 0) {
				// length of damaged springs does not match pattern
				if (n != pattern[index]) {
					return 0;
				}
				++index;
				// got to hitting the end of the pattern
				if (index == pattern.size()) {
					if (std::none_of(first, last, [](char c) {return c == DAMAGED; })) {
						return 1;
					}
					return 0;
				}
				n = 0;
			}
			
			if (*first == UNKNOWN) {
				*first = DAMAGED;
				arrangements += possible_arrangements(first, last, pattern, index, n);
				*first = OPERATIONAL;
				arrangements += possible_arrangements(first, last, pattern, index, n);
				*first = UNKNOWN;
				return arrangements;
			}
			++first;
		}
		// at the last character we should be on last index and have counted the same number of damaged
		if (index == pattern.size() - 1 && n == pattern.back()) {
			return 1;
		}
		// got to the end return 1 for the current pattern
		return 0;
	}

	template<typename T = int>
	T sum_records(const ConditionRecords<T>& records) {
		auto op = [](T n, Record<T> r) -> int {
			auto [springs, pattern] = r;
			T arrangements = possible_arrangements(springs.begin(), springs.end(), pattern, 0, 0);
			return n + arrangements;
			};

		return std::accumulate(records.begin(), records.end(), 0, op);
	}
}
