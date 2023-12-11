#include "day_11.h"

void day_11::print_answers() {
	std::cout << DAY_NAME; 

	// get grid
	const grid INPUT{file_parser::file_to_grid(INPUT_FILE)};

	// find galaxies
	const std::vector<std::pair<int64_t, int64_t>> GALAXY_LIST{ find_galaxies(INPUT) };

	// find empty rows & column indexes
	const std::vector<int64_t> EMPTY_ROWS{ find_empty_rows(INPUT) };
	const std::vector<int64_t> EMPTY_COLUMNS{ find_empty_columns(INPUT) };

	const int64_t PART_1 { sum_shortest_paths(GALAXY_LIST, EMPTY_ROWS, EMPTY_COLUMNS) };

	const int64_t FACTOR{ 999999 };

	const int64_t PART_2{ sum_shortest_paths(GALAXY_LIST, EMPTY_ROWS, EMPTY_COLUMNS, FACTOR) };

	std::cout << "Part 1: " << PART_1 << '\n';
	std::cout << "Part 1: " << PART_2 << '\n';

}
