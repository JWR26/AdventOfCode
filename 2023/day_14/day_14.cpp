#include "day_14.h"

void day_14::print_answers() {
	std::cout << DAY_NAME;

	auto t1 = std::chrono::high_resolution_clock::now();

	const std::vector<std::vector<char>> INPUT{ file_parser::file_to_grid(INPUT_FILE) };

	aoc::grid<char> grid{ INPUT };

	for (size_t c{}; c < grid._columns; ++c) {
		aoc::grid<char>::column_iterator first{ grid.column_begin(c) };
		aoc::grid<char>::column_iterator last{ grid.column_end(c) };

		tilt(first, last);
	}

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

void day_14::tilt_north(aoc::grid<char>& g) {
	for (size_t c{}; c < g._columns; ++c) {
		aoc::grid<char>::column_iterator first{ g.column_begin(c) };
		aoc::grid<char>::column_iterator last{ g.column_end(c) };

		tilt(first, last);
	}
}

void day_14::tilt_south(aoc::grid<char>& g) {
	//for (size_t c{}; c < g._columns; ++c) {
	//	aoc::grid<char>::reverse_column_iterator first{ g.column_rbegin(c) };
	//	aoc::grid<char>::reverse_column_iterator last{ g.column_rend(c) };

	//	tilt(first, last);
	//}
}

void day_14::tilt_east(aoc::grid<char>& g) {
	for (size_t r{}; r < g._rows; ++r) {
		aoc::grid<char>::row_iterator first{ g.row_begin(r) };
		aoc::grid<char>::row_iterator last{ g.row_end(r) };

		tilt(first, last);
	}
}

void day_14::tilt_west(aoc::grid<char>& g) {
	//for (size_t r{}; r < g._rows; ++r) {
	//	aoc::grid<char>::reverse_row_iterator first{ g.row_rbegin(r) };
	//	aoc::grid<char>::reverse_row_iterator last{ g.row_rend(r) };

	//	tilt(first, last);
	//}
}

void day_14::cycle(aoc::grid<char>& g) {
	tilt_north(g);
	tilt_west(g);
	tilt_south(g);
	tilt_east(g);
}

aoc::grid<char> day_14::spin_cycle(const aoc::grid<char>& grid, const size_t& n) {
	aoc::grid<char> spun_grid{ grid };
	
	std::vector<aoc::grid<char>> grids;

	grids.push_back(spun_grid);
	cycle(spun_grid);
	grids.push_back(spun_grid);

	size_t spins{};

	while (spun_grid != grid) {
		cycle(spun_grid);
		grids.push_back(spun_grid);
		++spins;
	}


	return grids[spins % n];
}
