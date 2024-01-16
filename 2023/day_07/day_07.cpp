#include "day_07.h"


std::vector<day_07::Hand> day_07::get_hands(const std::vector<std::string>& strings) {
	std::vector<day_07::Hand> hands;
	hands.reserve(strings.size());
	for (const std::string& str : strings) {
		hands.emplace_back(str);
	}
	return hands;
}


void day_07::print_answers() {
	std::cout << day_07::DAY_NAME << std::endl; 
	// get strings
	std::vector<std::string> input{ aoc::get_lines(day_07::INPUT_FILE) };

	std::vector<day_07::Hand> hands{ get_hands(input) };

	std::sort(hands.begin(), hands.end());

	std::cout << "Part 1: " << determine_winnings<long long>(hands) << '\n';

	for (Hand& h : hands) {
		h.apply_joker();
	}

	std::sort(hands.begin(), hands.end());

	std::cout << "Part 2: " << determine_winnings<uint64_t>(hands) << '\n';
}

int day_07::part_one(const std::string& input_file) {
	int answer{};
	return answer;
}

int day_07::part_two(const std::string& input_file) {
	int answer{};
	return answer;
}

