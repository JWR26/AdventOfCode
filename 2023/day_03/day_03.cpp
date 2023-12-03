#include "day_03.h"


void day_03::print_answers() {
	std::cout << day_03::DAY_NAME << '\n';

	auto [grid, positions] = parser::to_grid_with_positions(day_03::INPUT_FILE, [](char c) -> bool {return !isdigit(c) && c != '.'; });

	std::vector<std::vector<int>> schema_numbers = number_schema(grid);

	int part_1{}, part_2{}, prev{}, left{}, right{}, top{}, bottom{}, n{};

	std::vector<int> numbers;

	for (const auto& [row, column] : positions) {
		// find all neighbours
		left = column - 1;
		right = column + 2;
		top = row - 1;
		bottom = row + 2;

		for (int i{ top }; i < bottom; ++i) {
			for (int j{ left }; j < right; ++j) {
				n = schema_numbers[i][j];
				if (n != prev && n > 0) {
					numbers.push_back(n);
				}
				prev = n;
			}
			prev = 0;
		}
		
		part_1 += std::accumulate(numbers.begin(), numbers.end(), 0);
		
		if (schema_numbers[row][column] == -1 && numbers.size() == 2) {
			part_2 += numbers[0] * numbers[1];
		}

		numbers.clear();
	}
	std::cout << "Part 1: " << part_1 << '\n';
	std::cout << "Part 2: " << part_2 << '\n';
}

std::vector<std::vector<int>> day_03::number_schema(const std::vector<std::vector<char>>& grid) {
	// sliding window to allocate each point on the schema its integer value
	std::vector<std::vector<int>> numbers(grid.size(), std::vector<int>(grid.front().size(), 0));

	// variable declarations outside of the loop
	int n{}, index{}, r{};
	std::vector<char>::const_iterator rhs, lhs;

	// catching up occurs in three different scenarios - Lambda to the rescue
	auto catch_up = [&]() -> void {
		while (lhs != rhs) {
			numbers[r][index] = *lhs != '*' ? n : -1;
			++lhs;
			++index;
		}
		};

	for (const std::vector<char>& row : grid) {
		// lhs and rhs pointers for the sliding window - lhs will 'chase' the rhs
		lhs = row.begin();
		rhs  = row.begin();

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
