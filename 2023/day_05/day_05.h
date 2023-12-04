#pragma once

#include <chrono>
#include <iostream>
#include <string>


namespace day_05 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_04\\input.txt" };
	const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_04\\test.txt" };
	const std::string DAY_NAME{ "--- Day 4: Scratchcards ---" };

	void print_answers();
	int part_one(const std::string& input_file);
	int part_two(const std::string& input_file);
}
