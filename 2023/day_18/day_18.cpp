#include "day_18.h"

void day_18::print_answers() {
	std::cout << DAY_NAME;

	const std::vector<std::string> INPUT{ aoc::get_lines(INPUT_FILE) };

	const std::vector<vertex> TRENCH{ get_trench(INPUT) };

	const int64_t PART_1{ shoelace(TRENCH) };
		
	std::cout << "Part 1: " << PART_1 << '\n';

	const std::vector<vertex> HEX_TRENCH{ get_hex_trench(INPUT) };

	const int64_t PART_2{ shoelace(HEX_TRENCH) };

	std::cout << "Part 2: " << PART_2 << '\n';
}

std::vector<day_18::vertex> day_18::get_trench(const std::vector<std::string>& dig_plan) {
	std::vector<vertex> trench;
	trench.reserve(dig_plan.size());

	vertex current{ std::make_pair<int64_t, int64_t>(0,0) };

	for (const auto& str : dig_plan) {
		std::string::const_iterator it{ str.begin() };
		vertex dir{ DIRECTION.at(*it) };
		++it;
		int64_t meters{};
		while (*it != '(') {
			if (std::isdigit(*it)) {
				meters = meters * 10 + (*it - '0');
			}
			++it;
		}
		
		current.first += dir.first * meters;
		current.second += dir.second * meters;

		trench.emplace_back(current);
	}

	return trench;
}


std::vector<day_18::vertex> day_18::get_hex_trench(const std::vector<std::string>& dig_plan) {
	std::vector<vertex> trench;
	trench.reserve(dig_plan.size());

	vertex current{ std::make_pair<int64_t, int64_t>(0,0) };

	for (const auto& str : dig_plan) {
		std::string hex{ str.substr(str.find('#')+1, 6) };
		char hex_dir{ HEX_DIRECTION.at(hex.back()) };
		vertex dir{ DIRECTION.at(hex_dir) };
		
		std::stringstream ss;
		ss<< std::hex << hex.substr(0, 5); // chop off last char

		int64_t meters{};

		ss >> meters;

		current.first += dir.first * meters;
		current.second += dir.second * meters;

		trench.emplace_back(current);
	}

	return trench;
}


int64_t day_18::determinant(const vertex& a, const vertex& b) {
	return a.first * b.second - b.first * a.second;
}


int64_t day_18::shoelace(const std::vector<vertex>& vertices) {
	const size_t N{ vertices.size() };

	int64_t area{ static_cast<int64_t>(N) };

	for (size_t n{ 0 }; n < N; ++n) {
		// area of trapezoid
		vertex a{ vertices[n] };
		vertex b{ vertices[(n + 1) % N] }; // wrap last one

		area += determinant(a, b);

		// perimeter of line (-1) as only want cells between the vertices
		area += abs(b.first - a.first) + abs(b.second - a.second) - 1;
	}

	area /= 2;

	return ++area;
}