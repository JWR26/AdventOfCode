#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "file_parser.h"

namespace day_11 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_11\\input.txt" };
	const std::string DAY_NAME{ "--- Day 11: Cosmic Expansion ---\n" };
	const char GALAXY{ '#' };

	using grid = std::vector < std::vector<char>>;

	void print_answers();

	template<typename T = int64_t>
	std::vector<std::pair<T, T>> find_galaxies(const grid& g) {
		std::vector<std::pair<T, T>> galaxies;

		const T ROWS{ static_cast<T>(g.size()) };
		const T COLUMNS{ static_cast<T>(g.front().size()) };

		galaxies.reserve(ROWS * COLUMNS);

		for (T i{ 0 }; i < ROWS; ++i) {
			for (T j{ 0 }; j < COLUMNS; ++j) {
				if (g[i][j] == GALAXY) {
					galaxies.emplace_back(std::make_pair(i, j));
				}
			}
		}

		return galaxies;
	}

	template<typename T = int64_t>
	std::vector<T> find_empty_rows(const grid& g) {
		std::vector<T> empty_rows;
		
		T index{ 0 };
		for (const std::vector<char>& row : g) {
			if (!std::any_of(row.begin(), row.end(), [](const char c) {return c == GALAXY; })) {
				empty_rows.emplace_back(index);
			}
			++index;
		}

		return empty_rows;
	}

	template<typename T = int64_t>
	std::vector<T> find_empty_columns(const grid& g) {
		std::vector<T> empty_columns;

		const T COLUMNS{ static_cast<T>(g.front().size()) };
		
		for (T c{ 0 }; c < COLUMNS; ++c) {
			if (!std::any_of(g.begin(), g.end(), [&c](const std::vector<char> r) {return r[c] == GALAXY; })) {
				empty_columns.emplace_back(c);
			}
		}

		return empty_columns;
	}

	template<typename T = int64_t>
	T calculate_adjusted_difference(const T& a, const T& b, const std::vector<T>& v, const T& factor = 1) {
		T diff = abs(a - b);

		const T MIN{ std::min(a, b) };
		const T MAX{ std::max(a, b) };

		diff += std::count_if(v.begin(), v.end(), [&](T i) {return i > MIN && i < MAX; }) * factor;

		return diff;
	}

	template<typename T = int64_t>
	T calculate_adjusted_manhattan(const std::pair<T, T>& a, const std::pair<T, T>& b, const std::vector<T>& rows, const std::vector<T>& columns, const T& factor = 1) {
		T dx = calculate_adjusted_difference(a.first, b.first, rows, factor);
		T dy = calculate_adjusted_difference(a.second, b.second, columns, factor);

		return dx + dy;
	}

	template<typename T = int64_t>
	T sum_shortest_paths(const std::vector<std::pair<T, T>>& galaxies, const std::vector<T>& empty_rows, const std::vector<T>& empty_columns, const T& factor = 1) {
		T total{ 0 };

		for (auto first{ galaxies.begin() }; first != galaxies.end(); ++first) {
			for (auto second{ first + 1 }; second != galaxies.end(); ++second) {
				total += calculate_adjusted_manhattan(*first, *second, empty_rows, empty_columns, factor);
			}
		}

		return total;
	}
}

