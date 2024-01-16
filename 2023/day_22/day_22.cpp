#include "day_22.h"

void day_22::print_answers() {
	const std::string FILE{ aoc::get_test_file(2023, 22) };

	const std::string INPUT{ aoc::read_to_string(FILE) };

	std::vector<brick> snapshot{ get_bricks(INPUT) };

	std::sort(snapshot.begin(), snapshot.end(), compare_z);

	fall(snapshot);

	const std::vector<brick> CRITICAL_BRICKS{ disintegrate(snapshot) };

	const size_t PART_1{ snapshot.size() - CRITICAL_BRICKS.size() };

	const int PART_2{ sum_chain_reactions(snapshot, CRITICAL_BRICKS) };

	aoc::print_answer("--- Day 22: Sand Slabs ---", PART_1, PART_2);
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

		bricks.emplace_back(sm[0], x, y, z, l, w, h);

		start = sm[0].second;
	}

	return bricks;
}

bool day_22::compare_z(const brick& b1, const brick& b2) {
	if (b1.z < b2.z) {
		return true;
	}
	// ensures shorter of the vertical blocks comes
	return b1.z == b2.z && b1.height < b2.height;
}

std::vector<day_22::brick>& day_22::fall(std::vector<brick>& snapshot) {
	// hold the max z value and corresponding brick for x,y (x : [y : (z, brick)])
	std::unordered_map<int, std::unordered_map<int, std::pair<int, brick>>> max_z;

	for (brick& b : snapshot) {
		// find the max z under the blocks x,y coordinates
		int settle_z{};

		for (int x{ b.x }; x < b.x + b.length; ++x) {
			for (int y{ b.y }; y < b.y + b.width; ++y) {
				settle_z = std::max(settle_z, max_z[x][y].first);
			}
		}

		b.z = settle_z + 1;

		// find bricks with contact
		// store previous in case more than 1 cube overlap
		brick prev;

		for (int x{ b.x }; x < b.x + b.length; ++x) {
			for (int y{ b.y }; y < b.y + b.width; ++y) {
				if (max_z[x][y].first != b.z - 1) {
					continue;
				}
				if (max_z[x][y].second == prev) {
					continue;
				}

				b.supported_by.push_back(max_z[x][y].second);

				auto res{ std::find(snapshot.begin(), snapshot.end(),max_z[x][y].second) };
				res->supporting.push_back(b);
				prev = max_z[x][y].second;
			}
		}

		// update the max_z for x,y coordinates
		for (int x{ b.x }; x < b.x + b.length; ++x) {
			for (int y{ b.y }; y < b.y + b.width; ++y) {
				max_z[x][y].first = b.z + b.height - 1;
				max_z[x][y].second = b;
			}
		}
	}

	return snapshot;
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

int day_22::chain_reaction(const std::vector<brick>& stack, const brick& start) {
	std::unordered_set<std::string> disintegrated{};
	std::queue<brick> queue;
	queue.push(start);

	// hash table and lambda instead of tree with intersections to check that all neighbours are disintegrated
	auto is_disintegrated = [&disintegrated](const brick b) -> bool {
		return disintegrated.find(b.id) != disintegrated.end();
		};

	while (!queue.empty()) {
		brick b{ queue.front() };
		queue.pop();

		disintegrated.insert(b.id);

		for (const brick& s : b.supporting) {
			if (std::all_of(s.supported_by.begin(), s.supported_by.end(), is_disintegrated)) {
				queue.push(s);
			}
		}
	}

	// minus 1 as start brick is in disintegrated l
	return static_cast<int>(disintegrated.size()) - 1;
}

int day_22::sum_chain_reactions(const std::vector<brick>& stack, const std::vector<brick>& brick_list) {
	auto op = [&stack](int i, const brick b) -> int {
		return i + chain_reaction(stack, b);
		};

	return std::accumulate(brick_list.begin(), brick_list.end(), 0, op);
}