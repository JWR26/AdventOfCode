#include "day_01.h"

void day_01::print_answers() {
	std::cout << "--- Day 1: Trebuchet?! ---" << std::endl; 

	std::vector<std::string> input = parser::get_lines(input_file);

	std::cout << "Part 1: " << part_one(input) << '\n';
	std::cout << "Part 2: " << part_two(input) << '\n';
}

int day_01::part_one(const std::vector<std::string>& input) {
	auto calibration_value = [&] (int a, std::string s) -> int {
		int i = (*std::find_if(s.begin(), s.end(), std::isdigit) - '0') * 10;
		i += *std::find_if(s.rbegin(), s.rend(), std::isdigit) - '0';
		return a + i;
	};

	return std::accumulate(input.begin(), input.end(), 0, calibration_value);
}

int day_01::part_two(const std::vector<std::string>& input) {
	const std::vector<std::string> LETTERS = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	
	auto find_digit = [&](
		int d, // current digit
		size_t index, // index limit
		const std::function < size_t(std::string)> str_find, // return position of substring
		const std::function<bool(size_t, size_t)>& comp // comparison operator
		) -> int {

		int digit{ 0 };
		for (const auto& l : LETTERS) {
			++digit;
			size_t res = str_find(l);
			
			if (res == std::string::npos) {
				continue;
			}

			if (comp(res, index)) {
				index = res;
				d = digit;
			}
		}

		return d;
	};

	auto calibration_value = [&](int a, std::string s) -> int {
		auto first = std::find_if(s.begin(), s.end(), std::isdigit);
		std::string chunk(s.begin(), first);
		auto forward_find = [&chunk](const std::string& s) -> size_t { return chunk.find(s); };
		int i = find_digit(*first - '0', std::string::npos, forward_find, std::less_equal<size_t>()) * 10;

		auto last = std::find_if(s.rbegin(), s.rend(), std::isdigit);
		int index = s.size() - std::distance(s.rbegin(), last);
		chunk = s.substr(index);
		auto reverse_find = [&chunk](const std::string& s) -> size_t { return chunk.rfind(s); };
		i += find_digit(*last - '0', 0, reverse_find, std::greater_equal<size_t>());

		return a + i;
		};

	return std::accumulate(input.begin(), input.end(), 0, calibration_value);
}
