#include "day_16.h"

void day_16::print_answers() {
	std::cout << DAY_NAME;

	const std::vector<std::vector<char>> INPUT{ aoc::file_to_grid(INPUT_FILE) };

	grid g{ get_grid(INPUT) };

	beam start_1(0, -1, DIRECTION::RIGHT);

	std::vector<bool> energised_grid{ bounce_beam(g, start_1) };

	int part_1{ tiles_energised(g, start_1)};

	int part_2{ largest_energisation(g)};

	std::cout << "Part 1: " << part_1 << '\n';
	std::cout << "Part 2: " << part_2 << '\n';
}

bool day_16::on_grid(const grid& g, const beam& b) {
	if (b.row < 0 || b.column < 0) {
		return false;
	}
	
	return b.row < g.ROWS && b.column < g.COLUMNS;
}

void day_16::update_beam(beam& b) {
	switch (b.direction) 
	{
	case DIRECTION::LEFT:
		--b.column;
		break;
	case DIRECTION::RIGHT:
		++b.column;
		break;
	case DIRECTION::DOWN:
		++b.row;
		break;
	case DIRECTION::UP:
		--b.row;
		break;
	}
}

std::vector<bool> day_16::bounce_beam(const grid& g, const beam& start) {
	std::vector<bool> energised(g.DATA.size(), false);

	std::queue<beam> queue;
	queue.push(start);

	while (!queue.empty()) {
		beam b{ queue.front() };
		queue.pop();

		update_beam(b);
		
		// exit conditions
		if (!on_grid(g, b)) {
			continue;
		}

		const char TILE{ g.DATA[b.row * g.COLUMNS + b.column] };
		
		// handle splitters
		if (TILE == H_SPLIT || TILE == V_SPLIT) {
			// splitter already visited - exit to avoid infinte loop
			if (energised[b.row * g.COLUMNS + b.column]) {
				continue;
			}
			if (CAN_SPLIT.at(TILE).at(b.direction)) {
				std::pair<DIRECTION, DIRECTION> split_directions = SPLIT.at(b.direction);
				b.direction = split_directions.first;
				queue.push(b);
				b.direction = split_directions.second;
			}
		}

		// handle mirrors
		if (TILE == L_MIRROR || TILE == R_MIRROR) {
			b.direction = MIRROR.at(TILE).at(b.direction);
		}

		// beam travelling in straight line not hitting any special tiles
		energised[b.row * g.COLUMNS + b.column] = true;
		queue.push(b);
	}

	return energised;
}

day_16::grid day_16::get_grid(const std::vector<std::vector<char>>& input) {
	int rows{ static_cast<int>(input.size()) };
	int cols{ static_cast<int>(input.front().size())};

	std::vector<char> values;
	for (const auto& v : input) {
		values.insert(values.end(), v.begin(), v.end());
	}

	return grid(values, rows, cols);
}

int day_16::tiles_energised(const grid& g, const beam& b) {
	std::vector<bool> energised_grid{ bounce_beam(g, b) };
	int n { static_cast<int>(std::count(energised_grid.begin(), energised_grid.end(), true)) };
	return n;
}

int day_16::largest_energisation(const grid& g) {
	std::vector<int> energisation_numbers;

	for (int i{}; i < g.COLUMNS; ++i) {
		beam start(-1, i, DIRECTION::DOWN);
		energisation_numbers.emplace_back(tiles_energised(g, start));
		start = beam(g.ROWS, i, DIRECTION::UP);
		energisation_numbers.emplace_back(tiles_energised(g, start));
	}

	for (int i{}; i < g.ROWS; ++i) {
		beam start(i, -1, DIRECTION::RIGHT);
		energisation_numbers.emplace_back(tiles_energised(g, start));
		start = beam(i, g.COLUMNS, DIRECTION::LEFT);
		energisation_numbers.emplace_back(tiles_energised(g, start));
	}

	int max = *std::max_element(energisation_numbers.begin(), energisation_numbers.end());

	return max;
}
