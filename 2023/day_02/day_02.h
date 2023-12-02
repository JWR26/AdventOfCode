#pragma once

#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include <parser.h>

struct Game {
	int id{}, max_red{}, max_blue{}, max_green{};

	bool is_possible() const {
		return max_red < 13 && max_green < 14 && max_blue < 15;
	}

	int cube_power() const {
		return max_red * max_green * max_blue;
	}
};

const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_02\\input.txt" };
const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_02\\test.txt" };


namespace day_02 {
	void print_answers();
	int part_one(const std::vector<Game>& input);
	int part_two(const std::vector<Game>& input);
	Game to_game(const std::string& text);
}
 