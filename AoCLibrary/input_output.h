#pragma once

#include <iostream>
#include <format>
#include <string>

namespace aoc {
	std::string get_input_file(const int& year, const int& day);

	std::string get_test_file(const int& year, const int& day);

	std::string get_test_file(const int& year, const int& day, const char& suffix);

	template<typename T, typename U>
	void print_answer(const T& part_1, const U& part_2) {
		std::cout << std::format("Part 1: {}\nPart 2: {}", part_1, part_2) << std::endl;
	}

	template<typename T, typename U>
	void print_answer(const std::string& title, const T& part_1, const U& part_2) {
		std::cout << std::format("\n{}\n\nPart 1: {}\nPart 2: {}", title, part_1, part_2) << std::endl;
	}
}
