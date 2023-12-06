#include "day_02.h"

void day_02::print_answers() {
	std::cout << "--- Day 2: Cube Conundrum ---" << std::endl; 

	auto begin = std::chrono::high_resolution_clock::now();

	std::vector<std::string> input = parser::get_lines(INPUT_FILE);

	std::vector<Game> game_list;

	for (const std::string& s : input) {
		game_list.push_back(to_game(s));
	}

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Part 1: " << part_one(game_list) << '\n';
	std::cout << "Part 2: " << part_two(game_list) << '\n';

	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";
}

int day_02::part_one(const std::vector<Game>& game_list) {
	// convert list of strings to list of games
	// ensure sufficient space is reserved for all games to avoid reallocation
	auto total_score = [](int i, const Game& g) -> int {
		if (g.is_possible()) {
			return i + g.id;
		}
		return i;
		};

	return std::accumulate(game_list.begin(), game_list.end(), 0, total_score);
	
	/*
	// classic for loop in place of algorithm:
	int score{};
	for (const auto& g : game_list) {
		if (g.is_possible()) {
			score += g.id;
		}
	}

	return score;*/
}

int day_02::part_two(const std::vector<Game>& game_list) {
	auto total_score = [](int i, const Game& g) -> int {
		return i + g.cube_power();
		};

	return std::accumulate(game_list.begin(), game_list.end(), 0, total_score);
}

Game day_02::to_game(const std::string& text) {
	Game game;

	auto max_int = [&](std::regex rgx) -> int {
		int max{};
		std::smatch match;
		std::string temp(text);
		while (std::regex_search(temp, match, rgx)) {
			int n = std::stoi(match[1].str());
			max = n > max ? n : max;
			temp = match.suffix();
		}
		return max;
	};

	game.id = max_int(std::regex("Game (\\d+)"));
	game.max_red = max_int(std::regex("(\\d+) r"));
	game.max_green = max_int(std::regex("(\\d+) g"));
	game.max_blue = max_int(std::regex("(\\d+) b"));

	return game;
}