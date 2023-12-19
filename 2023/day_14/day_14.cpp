#include "day_14.h"

void day_14::print_answers() {
	std::cout << DAY_NAME;

	auto t1 = std::chrono::high_resolution_clock::now();

	const std::vector<std::vector<char>> INPUT{ file_parser::file_to_grid(INPUT_FILE) };

	aoc::grid<char> grid{ INPUT };

	// std::cout << grid << '\n';

	for (size_t c{}; c < grid._columns; ++c) {
		aoc::grid<char>::column_iterator first{ grid.column_begin(c) };
		aoc::grid<char>::column_iterator second{ grid.column_begin(c) };

		while (second != grid.column_end(c)) {
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
		}
	}

	// std::cout << grid << '\n';

	int part_1{};

	for (size_t r{}; r < grid._rows; ++r) {
		aoc::grid<char>::row_iterator r_it{ grid.row_begin(r) };
		while (r_it != grid.row_end(r)) {
			if (*r_it == 'O') {
				part_1 += grid._rows - r;
			}
			++r_it;
		}
	}

	auto t2 = std::chrono::high_resolution_clock::now();

	std::cout << "Part 1: " << part_1 << '\n';

	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
}
