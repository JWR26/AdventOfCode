#include "day_09.h"

void day_09::print_answers() {
	std::cout << day_09::DAY_NAME; 
	// input as list of integer lists
	std::vector<std::vector<long long>> input = file_parser::get_lines_as_number_lists<long long>(day_09::INPUT_FILE);
	// predict all next values
	// // find total of predictions
	std::cout << "Part 1: " << sum_extrapolated_values<long long>(input) << '\n';

	auto reverse = [](std::vector<long long>& v) -> void { std::reverse(v.begin(), v.end()); };
	std::for_each(input.begin(), input.end(), reverse);

	std::cout << "Part 2: " << sum_extrapolated_values<long long>(input);
}
