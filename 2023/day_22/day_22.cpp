#include "day_22.h"

void day_22::print_answers() {
	const std::string FILE{ aoc::get_input_file(2023, 22) };

	const std::string INPUT{ aoc::read_to_string(FILE) };

	std::vector<brick> snapshot{ get_bricks(INPUT) };

	std::sort(snapshot.begin(), snapshot.end(), compare_z);

	fall(snapshot);

	establish_supports(snapshot);

	const std::vector<brick> CRITICAL_BRICKS{ disintegrate(snapshot) };

	const size_t PART_1{ snapshot.size() - CRITICAL_BRICKS.size() };

	aoc::print_answer("--- Day 22: Sand Slabs ---", PART_1, '?');
}


std::vector<day_22::brick> day_22::get_bricks(const std::string& str) {
	std::vector<brick> bricks;
	
	const std::regex PATTERN{ "(\\d+),(\\d+),(\\d+)~(\\d+),(\\d+),(\\d+)" };

	std::string::const_iterator start{ str.begin() };
	std::string::const_iterator end{ str.end() };
	std::smatch sm;

	while (std::regex_search(start, end, sm, PATTERN)) {
		int x{ std::stoi(sm[1].str()) };
		int y{ std::stoi(sm[2].str()) };
		int z{ std::stoi(sm[3].str()) };

		int l{ std::stoi(sm[4].str()) - x + 1 };
		int w{ std::stoi(sm[5].str()) - y + 1 };
		int h{ std::stoi(sm[6].str()) - z + 1 };

		bricks.emplace_back(x, y, z, l, w, h);

		start = sm[0].second;
	}

	return bricks;
}

bool day_22::compare_z(const brick& b1, const brick& b2) {
	return b1.z < b2.z;
}

std::vector<day_22::brick>& day_22::fall(std::vector<brick>& snapshot) {
	// hold the max z values in the x & y columns
	std::unordered_map<int, int> max_z_x{}, max_z_y{};

	auto max_z = [](int from, int to, std::unordered_map<int, int>& in) -> int {
		int max{};
		for (from; from < to; ++from) {
			max = std::max(max, in[from]);
		}
		return max;
		};

	auto update_max_z = [](int from, int to, const int& z, std::unordered_map<int, int>& in) ->std::unordered_map<int, int>& {
		for (from; from < to; ++from) {
			in[from] = z;
		}

		return in;
	};

	for (brick& b : snapshot) {
		// find max z under block in x & y axis
		int zx{ max_z(b.x, b.x + b.length, max_z_x) };
		int zy{ max_z(b.y, b.y + b.width, max_z_y) };

		// z is the row above the min settle point
		b.z = std::min(zx, zy) + 1;

		// update the max_z for x & y axis
		update_max_z(b.x, b.x + b.length, b.z, max_z_x);
		update_max_z(b.y, b.y + b.width, b.z, max_z_y);
	}

	return snapshot;
}

std::vector<day_22::brick>& day_22::establish_supports(std::vector<brick>& stack) {
	std::unordered_map<int, std::vector<brick>> brick_tops;
	
	auto overlap = [](int top_from, int top_to, int bottom_from, int bottom_to) -> bool {
		if (top_from < bottom_from) {
			return top_to > top_from;
		}
		return top_from < bottom_to;
	};

	for (auto top{ stack.begin() }; top != stack.end(); ++top) {
		brick_tops[top->z + top->height].push_back(*top);

		for (brick& b : brick_tops[top->z]) {
			if (!overlap(top->x, top->x + top->length, b.x, b.x + b.length)) {
				continue;
			}

			if (!overlap(top->y, top->y + top->width, b.y, b.y + b.width)) {
				continue;
			}

			top->supported_by.push_back(b);
			b.supporting.push_back(*top);
		}
	}

	return stack;
}

std::vector<day_22::brick> day_22::disintegrate(const std::vector<brick>& stack) {
	std::vector<brick> critical;

	for (const brick& b : stack) {
		if (b.supported_by.size() != 1) {
			continue;
		}

		if (std::find(critical.begin(), critical.end(), b.supported_by.front()) == critical.end()) {
			critical.push_back(b.supported_by.front());
		}
	}


	return critical;
}