#pragma once

#include <iostream>
#include <vector>

namespace day_06 {
	const std::vector<std::pair<int, int>> TEST_INPUT{
		std::make_pair(7, 9),
		std::make_pair(15, 40),
		std::make_pair(30, 200),
	};

	const std::vector<std::pair<int, int>> INPUT{
	std::make_pair(38, 241),
	std::make_pair(94, 1549),
	std::make_pair(79, 1074),
	std::make_pair(70, 1091),
	};

	const std::pair<long long, long long> TEST_2(std::make_pair(71530, 940200));
	const std::pair<long long, long long> INPUT_2(std::make_pair(38947970, 241154910741091));

	void print_answers();
	int part_one();
	long long part_two();
}

