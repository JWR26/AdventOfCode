#include "day_02.h"

void day_02::print_answers() {
	std::cout << "Not implemented - Insert day name here" << std::endl; 

	std::string input_file{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2019\\day_02\\input.txt" };

	std::cout << "Part 1: " << part_one(input_file) << '\n';
	std::cout << "Part 2: " << part_two(input_file) << '\n';
}

int day_02::part_one(const std::string& input_file) {
	std::vector<int> input = intcode::get_programme(input_file);

	Intcode computer(input);
	// update position 1 with 12 and 2 with 2
	computer.update_position(1, 12);
	computer.update_position(2, 2);

	return computer.run_programme()[0];
}

int day_02::part_two(const std::string& input_file) {
	std::vector<int> input = intcode::get_programme(input_file);

	Intcode computer(input);

	int noun{ 0 }, verb{ 0 };

	for (int i = 1; i < 100; ++i) {
		for (int j = 1; j < 100; ++j) {
			computer.update_position(1, i);
			computer.update_position(2, j);
			if (computer.run_programme()[0] == 19690720) {
				noun = i;
				verb = j;
			}
			computer.reset_programme();
		}
	}

	return 100 * noun + verb;;
}
