#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include "file_parser.h"

namespace day_09 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_09\\input.txt" };
	const std::string DAY_NAME{ "--- Day 9: Mirage Maintenance ---\n" };

	void print_answers();

	template<typename T = int>
	T predict_next(const std::vector<T>& values, const int& offset = 0) {
		std::vector<T> differences(values);

		std::adjacent_difference(differences.begin() + offset, differences.end(), differences.begin() + offset);
		// check from offset + 1 because adj_diff stored first value at first position
		if (std::all_of(differences.begin() + offset + 1, differences.end(), [](int i) { return i == 0; })) {
			return values.back();
		}
		return values.back() + predict_next(differences, offset + 1);
	}

	template<typename T = int>
	T sum_extrapolated_values(const std::vector<std::vector<T>>& rapport) {
		auto op = [](int n, const std::vector<T>& v) -> int {
			return n + predict_next(v);
			};

		return std::accumulate(rapport.begin(), rapport.end(), 0, op);
	}
}
