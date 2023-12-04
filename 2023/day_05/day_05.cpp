#include "day_05.h"

void day_05::print_answers() {
	std::cout << day_05::DAY_NAME << std::endl;

	auto begin = std::chrono::high_resolution_clock::now();

	int part_1{ part_one(day_05::TEST_FILE) };
	int part_2{ part_two(day_05::TEST_FILE) };

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Part 1: " << part_1 << '\n';
	std::cout << "Part 2: " << part_2 << '\n';

	float t = float(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000;

	std::cout << "Time: " << t << " ms\n";
}

int day_05::part_one(const std::string& input_file) {
	int answer{};
	return answer;
}

int day_05::part_two(const std::string& input_file) {
	int answer{};
	return answer;
}
