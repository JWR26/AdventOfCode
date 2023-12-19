#include "day_14.h"

void day_14::print_answers() {
	std::cout << DAY_NAME;

	const std::vector<std::vector<char>> INPUT{ file_parser::file_to_grid(INPUT_FILE) };

	aoc::grid<char> grid{ INPUT };

	std::cout << grid;

	for (size_t c{}; c < grid._columns; ++c) {
		aoc::grid<char>::column_iterator first{ grid.column_begin(c) };
		aoc::grid<char>::column_iterator second{ grid.column_begin(c) };

		while (second != grid.column_end(c)) {
			if (first == second) {
				++second;
				continue;
			}

			if (*first == 'O') {
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

	std::cout << '\n' << '\n' << grid;

}
