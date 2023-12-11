#include "day_09.h"

void day_09::print_answers() {
	std::cout << day_09::DAY_NAME; 

	std::vector<std::vector<long long>> input = file_parser::get_lines_as_number_lists<long long>(day_09::INPUT_FILE);

	std::cout << "Part 1: " << sum_extrapolated_values<long long>(input) << '\n';

	// reverse each list for part 2
	auto reverse = [](std::vector<long long>& v) -> void { std::reverse(v.begin(), v.end()); };
	std::for_each(input.begin(), input.end(), reverse);

	std::cout << "Part 2: " << sum_extrapolated_values<long long>(input) << '\n';
}
