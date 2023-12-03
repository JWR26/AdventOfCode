#include "day_03.h"


void day_03::print_answers() {
	std::cout << day_03::DAY_NAME << std::endl; 

	std::vector<std::vector<char>> raw_schematic = parser::file_to_grid(day_03::INPUT_FILE);
	std::vector<std::vector<int>> schema_numbers = number_schema(raw_schematic);
	std::vector<std::vector<bool>> adjacency_table = generate_adjacency_table(raw_schematic);
	
	std::cout << "Part 1: " << part_one(schema_numbers, adjacency_table) << '\n';

	std::cout << "Part 2: " << part_two(schema_numbers, raw_schematic) << '\n';
}

int day_03::part_one(const std::vector<std::vector<int>>& schematic, const std::vector<std::vector<bool>>& adjacency_table) {
	int answer{}, prev{}, r{}, c{};

	for (const std::vector<int>& row : schematic) {
		for (const int& part_number : row) {
			if (adjacency_table[r][c]) {
				// numbers adjacent to multiple symbols are not considered
				if (part_number != prev) {
					answer += part_number;
				}
				// last adjacent number
				prev = part_number;
			}
			++c;
		}
		++r;
		prev = 0;
		c = 0;
	}

	return answer;
}

int day_03::part_two(const std::vector<std::vector<int>>& schema_numbers, std::vector<std::vector<char>>& raw_schema) {
	int answer{}, prev{}, r{}, c{};

	for (const std::vector<char>& row : raw_schema) {
		for (const char& id : row) {
			if (id == '*') {
				// find all neighbours
				int left{ c > 1 ? c - 1 : 0 };
				int right{ c < row.size() - 2 ? c + 2 : static_cast<int>(row.size())};
				int top{ r > 1 ? r - 1 : 0 };
				int bottom{ r < raw_schema.size() - 2 ? r + 2 : static_cast<int>(raw_schema.size()) };
				std::vector<int> numbers;
				for (int i{ top }; i < bottom; ++i) {
					for (int j{ left }; j < right; ++j) {
						int n{ schema_numbers[i][j] };
						if (n != prev && n != 0) {
							numbers.push_back(n);
						}
						prev = n;
					}
					prev = 0;
				}
				if (numbers.size() == 2) {
					answer += numbers[0] * numbers[1];
				}

			}
			++c;
		}
		++r;
		c = 0;
		prev = 0;
	}

	return answer;
}

std::vector<std::vector<int>> day_03::number_schema(const std::vector<std::vector<char>>& grid) {
	// sliding window to allocate each point on the schema its integer value
	std::vector<std::vector<int>> numbers(grid.size(), std::vector<int>(grid.front().size(), 0));

	// variable declarations outside of the loop
	int n{};
	int index{}; // column counter
	int r{}; // counter for the row

	for (const std::vector<char>& row : grid) {
		// lhs and rhs pointers for the sliding window - lhs will 'chase' the rhs
		auto lhs(row.begin());
		auto rhs(row.begin());

		// catching up occurs in three different scenarios
		auto catch_up = [&]() -> void {
			while (lhs != rhs) {
				numbers[r][index] = n;
				++lhs;
				++index;
			}
			};

		while (rhs != row.end()) {
			if (isdigit(*rhs)) {
				if (n == 0) {
					catch_up();
				}
				n = n * 10 + (*rhs + -'0');
				++rhs;
				continue;
			}
			// hit a 'non digit'
			catch_up();
			// both iterators to same letter, move rhs to next
			++rhs;
			n = 0;
		}

		// rhs has reached the end of the row catch up lhs to rhs before moving to next row
		catch_up();
		++r;
		index = 0;
		n = 0;
	}

	return numbers;
}

std::vector<std::vector<bool>> day_03::generate_adjacency_table(const std::vector<std::vector<char>>& grid) {
	size_t rows{ grid.size() };
	size_t columns{ grid.front().size() };
	
	std::vector<std::vector<bool>> table(rows, std::vector<bool>(columns, false));

	auto pred = [](char c) -> bool {return c != '.'; };

	for (int i{ 1 }; i < rows; ++i) {
		for (int j{ 1 }; j < columns; ++j) {
			bool is_symbol = (!isdigit(grid[i][j]) && pred(grid[i][j]));
			bool up_symbol = (!isdigit(grid[i-1][j]) && pred(grid[i-1][j]));
			bool left_symbol = (!isdigit(grid[i][j-1]) && pred(grid[i][j-1]));
			bool diagonal_symbol = (!isdigit(grid[i-1][j-1]) && pred(grid[i-1][j-1]));
			// include "self" in the evaluation to avoid setting a true back to false (ie. neighbour up-left is symbol but all bottom/right are not)
			table[i][j] = table[i][j] || is_symbol || up_symbol || left_symbol || diagonal_symbol;
			table[i - 1][j] = table[i - 1][j] || is_symbol || up_symbol || left_symbol || diagonal_symbol;
			table[i - 1][j - 1] = table[i - 1][j - 1] || is_symbol || up_symbol || left_symbol || diagonal_symbol;;
			table[i][j - 1] = table[i][j - 1] || is_symbol || up_symbol || left_symbol || diagonal_symbol;;
		}
	}

	return table;
}
