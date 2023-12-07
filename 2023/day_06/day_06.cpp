#include "day_06.h"

template<typename T>
T ways_to_win(std::pair<T, T> race) {
	const auto& [time, distance] = race;
	for (T i{ 1 }; i < time; ++i) {
		T d{ i * (time - i) };

		if (d >= distance) {
			return (time - (2 * i) + 1);
		}
	}

	return 0;
}

void day_06::print_answers() {
	std::cout << "--- Day 6: Wait For It ---" << std::endl; 

	std::cout << "Part 1: " << part_one() << '\n';
	std::cout << "Part 2: " << part_two() << '\n';
}

int day_06::part_one() {
	int product{ 1 };

	for (const auto& race : INPUT) {
		product *= ways_to_win(race);
	}

	return product;
}

long long day_06::part_two() {
	return ways_to_win(INPUT_2);
}