#include "day_17.h"

void day_17::print_answers() {
	std::cout << DAY_NAME;

	auto t1{ std::chrono::high_resolution_clock::now() };

	const std::vector<std::vector<char>> INPUT{ file_parser::file_to_grid(INPUT_FILE) };

	const std::shared_ptr<grid> CITY{ std::make_shared<grid>(get_grid(INPUT)) };

	int64_t part_1{ find_min_heat_loss(CITY, 0, MAX_CRUCIBLE) };

	auto t2{ std::chrono::high_resolution_clock::now() };
	
	std::cout << "Part 1: " << part_1 << '\n';
	std::cout << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1) << '\n';

	int64_t part_2{ find_min_heat_loss(CITY, MIN_ULTRA, MAX_ULTRA) };
	
	auto t3{ std::chrono::high_resolution_clock::now() };
	
	std::cout << "Part 2: " << part_2 << '\n';
	std::cout << std::chrono::duration_cast<std::chrono::seconds>(t3 - t2) << '\n';

}

void day_17::update_crucible(crucible& c) {
	switch (c.direction)
	{
	case DIRECTION::LEFT:
		--c.column;
		break;
	case DIRECTION::RIGHT:
		++c.column;
		break;
	case DIRECTION::DOWN:
		++c.row;
		break;
	case DIRECTION::UP:
		--c.row;
		break;
	}
	++c.consecutive_moves;
}

bool day_17::on_grid(const std::shared_ptr<grid> g, const crucible& c) {
	return c.row < g->ROWS && c.column < g->COLUMNS;
}

day_17::grid day_17::get_grid(const std::vector<std::vector<char>>& input) {
	size_t rows{ input.size() };
	size_t cols{ input.front().size() };

	std::vector<int> values;

	auto to_int = [](const char& c) -> int {return c - '0'; };

	for (const auto& v : input) {
		std::transform(v.begin(), v.end(), std::back_inserter(values), to_int);
	}

	return grid(values, rows, cols);
}

int64_t day_17::find_min_heat_loss(const std::shared_ptr<grid> g, const int& min_turn, const int& max_straight) {

	std::priority_queue<crucible, std::vector<crucible>, std::greater<crucible>> queue;

	visited_blocks visited;

	crucible start(g, 0, 0, DIRECTION::RIGHT, 0, 0);

	queue.push(start); // start top left facing right
	visited[start] = start;


	auto at_end = [&g](const crucible& c) -> bool {
		return c.row == g->ROWS - 1 && c.column == g->COLUMNS - 1;
		};

	while (!queue.empty()) {
		crucible c{ queue.top() };
		queue.pop();

		// can stop at end
		if (at_end(c) && !(c.consecutive_moves < min_turn)) {
			return c.heat_loss;
		}

		update_crucible(c);

		if (!on_grid(g, c) || c.consecutive_moves > max_straight) {
			continue;
		}

		c.heat_loss += g->DATA[c.row * g->COLUMNS + c.column];

		queue.push(c);

		// can't turn
		if (c.consecutive_moves < min_turn) {
			continue;
		}

		for (const DIRECTION& d : TURN_DIRECTIONS.at(c.direction)) {
			// create a copy with a new direction and enqueue
			// direction changed so reset current moves to 0!
			crucible next(g, c.row, c.column, d, 0, c.heat_loss);
			if (visited.find(next) == visited.end()) {
				queue.push(next);
				visited[next] = c;
			}
		}

	}

	return -1;
}
