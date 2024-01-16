#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "file_parser.h"
#include "grid.h"
#include "input_output.h"

namespace day_14 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_14\\input.txt" };
	const std::string DAY_NAME{ "--- Day 14: Parabolic Reflector Dish ---" };

	void print_answers();

	template<class ForwardIterator>
	void tilt(ForwardIterator& first, ForwardIterator& last) {
		ForwardIterator second{ first };

		while (second != last) {
			if (first == second) {
				++second;
				continue;
			}

			if (*first == 'O' || *first == '#') {
				++first;
				continue;
			}

			if (*second == '.') {
				++second;
				continue;
			}

			if (*second == 'O' && *first == '.') {
				std::iter_swap(first, second);
				continue;
			}

			if (*second == '#') {
				++second;
				first = second;
				continue;
			}
		};
	}

	void tilt_north(aoc::grid<char>& g);
	void tilt_south(aoc::grid<char>& g);
	void tilt_east(aoc::grid<char>& g);
	void tilt_west(aoc::grid<char>& g);

	void cycle(aoc::grid<char>& g);

	aoc::grid<char> spin_cycle(const aoc::grid<char>& grid, const size_t& n);

	int calculate_north_load(aoc::grid<char>& grid);
}
