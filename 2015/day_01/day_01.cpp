#include "day_01.h"

void day_01::print_answers() {
	std::cout << "--- Day 1: Not Quite Lisp ---" << std::endl; 

	std::string input = parser::read_to_string("C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2015\\day_01\\input_01.txt");

	std::cout << "Part 1: " << part_one(input) << '\n';
	std::cout << "Part 2: " << part_two(input) << '\n';
}

int day_01::part_one(const std::string& input_file) {
	return std::count(input_file.begin(), input_file.end(), '(') - std::count(input_file.begin(), input_file.end(), ')');
}

int day_01::part_two(const std::string& input_file) {
	int floor{0};
	int limit{ static_cast<int>(input_file.size()) };
	for (int i{ 0 }; i < limit; ++i) {
		floor += (input_file[i] == '(') ? 1 : -1;
		if (floor < 0) {
			return i+1;
		}
	}
	return -1;
}
