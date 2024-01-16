#include "day_02.h"

namespace day_02 {

	void print_answers() {
		std::cout << "--- Day 2: Cube Conundrum ---" << std::endl;

		auto begin = std::chrono::high_resolution_clock::now();

		std::vector<std::string> input = aoc::get_lines(INPUT_FILE);

		std::vector<Game> game_list{ to_game_list(input) };

		auto end = std::chrono::high_resolution_clock::now();

		std::cout << "Part 1: " << sum_possible_game_ids(game_list) << '\n';
		std::cout << "Part 2: " << sum_cube_powers(game_list) << '\n';

		std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";
	}

	Game to_game(const std::string& text) {
		Game game;

		std::string::const_iterator it{ text.begin() };
		int n{ 0 };
		while (it != text.end()) {
			if (isdigit(*it)) {
				n = n * 10 + (*it - '0');
			}
			else if (*it == ' ' || n == 0) {
				++it;
				continue;
			}
			else if (*it == ':') {
				game.id = n;
				n = 0;
			}
			else if (*it == 'r') {
				game.max_red = n > game.max_red ? n : game.max_red;
				n = 0;
			}
			else if (*it == 'g') {
				game.max_green = n > game.max_green ? n : game.max_green;
				n = 0;
			}
			else if (*it == 'b') {
				game.max_blue = n > game.max_blue ? n : game.max_blue;
				n = 0;
			}
			++it;
		}

		return game;

	}

	std::vector<Game> to_game_list(const std::vector<std::string>& list) {
		std::vector<Game> game_list;

		for (const std::string& s : list) {
			game_list.push_back(to_game(s));
		}

		return game_list;
	}

	bool is_possible(const Game& g) {
		return g.max_red < 13 && g.max_green < 14 && g.max_blue < 15;
	}

	int cube_power(const Game& g) {
		return g.max_red * g.max_green * g.max_blue;
	}

	int sum_possible_game_ids(const std::vector<Game>& game_list) {
		// convert list of strings to list of games
		// ensure sufficient space is reserved for all games to avoid reallocation
		auto total_score = [](int i, const Game& g) -> int {
			if (is_possible(g)) {
				return i + g.id;
			}
			return i;
			};

		return std::accumulate(game_list.begin(), game_list.end(), 0, total_score);
	}

	int sum_cube_powers(const std::vector<Game>& game_list) {
		auto total_score = [](int i, const Game& g) -> int {
			return i + cube_power(g);
			};

		return std::accumulate(game_list.begin(), game_list.end(), 0, total_score);
	}

}