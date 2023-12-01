#include "day_01.h"

void day_01::print_answers() {
	std::cout << "\n--- Day 1: The Tyranny of the Rocket Equation ---\n" << std::endl; 

	std::cout << "Part 1: " << part_one<int>("input.txt") << '\n';
	std::cout << "Part 2: " << part_two<int>("input.txt") << '\n';
}

int day_01::fuel_for_module(int mass) {
	int fuel = mass / 3 - 2;
	if (fuel < 1) {
		return 0;
	}
	return fuel;
}

int day_01::fuel_for_module_and_fuel(int mass) {
	int fuel = mass / 3 - 2;
	if (fuel < 1) {
		return 0;
	}
	return fuel + fuel_for_module_and_fuel(fuel);
}

template<typename T>
T part_one(const std::string& input_file) {
	T answer{};
	return answer;
}

template<typename T>
T part_two(const std::string& input_file) {
	T answer{};
	return answer;
}
