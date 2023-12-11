#include "day_11.h"

void day_11::print_answers() {
	std::cout << DAY_NAME; 

	// get grid
	const grid INPUT{file_parser::file_to_grid(INPUT_FILE)};

	// find galaxies
	const std::vector<std::pair<long long, long long>> GALAXY_LIST{ find_galaxies<long long>(INPUT) };

	// find empty rows & column indexes
	const std::vector<long long> EMPTY_ROWS{ find_empty_rows<long long>(INPUT) };
	const std::vector<long long> EMPTY_COLUMNS{ find_empty_columns<long long>(INPUT) };

	const long long PART_1 { sum_shortest_paths<long long>(GALAXY_LIST, EMPTY_ROWS, EMPTY_COLUMNS) };

	const long long PART_2{ sum_shortest_paths<long long>(GALAXY_LIST, EMPTY_ROWS, EMPTY_COLUMNS, 999999) };

	std::cout << "Part 1: " << PART_1 << '\n';
	std::cout << "Part 1: " << PART_2 << '\n';

}
