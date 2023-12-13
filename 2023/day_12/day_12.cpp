#include "day_12.h"

void day_12::print_answers() {
	std::cout << DAY_NAME; 

	const std::vector<std::string> INPUT{ file_parser::get_lines(INPUT_FILE) };

	ConditionRecords records{ get_records(INPUT) };

	int part_1{ sum_records(records) };

	std::cout << "Part 1: " << part_1 << '\n';

}

