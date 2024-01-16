#include "input_output.h"

std::string aoc::get_input_file(const int& year, const int& day) {
	return std::format("C:\\Users\\jonat\\source\\repos\\AdventOfCode\\files\\input\\{}\\{}.txt", year, day);
}

std::string aoc::get_test_file(const int& year, const int& day) {
	return std::format("C:\\Users\\jonat\\source\\repos\\AdventOfCode\\files\\test\\{}\\{}.txt", year, day);
}

std::string aoc::get_test_file(const int& year, const int& day, const char& suffix) {
	return std::format("C:\\Users\\jonat\\source\\repos\\AdventOfCode\\files\\test\\{}\\{}_{}.txt", year, day, suffix);
}