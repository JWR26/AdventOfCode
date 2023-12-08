#pragma once

#include <chrono>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "file_parser.h"


namespace day_02 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_02\\input.txt" };
	const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_02\\test.txt" };

	struct Game {
		int id{}, max_red{}, max_green{}, max_blue{};
	};

	Game to_game(const std::string& text);

	std::vector<Game> to_game_list(const std::vector<std::string>& list);

	bool is_possible(const Game& g);
	int cube_power(const Game& g);

	void print_answers();
	int sum_possible_game_ids(const std::vector<Game>& input);
	int sum_cube_powers(const std::vector<Game>& input);
	
}
 