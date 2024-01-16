#include "day_15.h"


void day_15::print_answers() {
	std::cout << DAY_NAME;

	const std::vector<std::string> INPUT{ aoc::split_file_by(INPUT_FILE, ',') };

	const int part_1{ sum_sequence(INPUT) };

	const std::map<int, std::list<lens>> BOXES{ fill_boxes(INPUT) };

	const int part_2{ calculate_focal_power(BOXES) };

	std::cout << "Part 1: " << part_1 << '\n';
	std::cout << "Part 2: " << part_2 << '\n';

}

int day_15::hash_char(const char& c, const int& i) {
	int hash{i};
	
	hash += static_cast<int>(c);
	hash *= 17;
	hash %= 256;

	return hash;
}

int day_15::hash_string(const std::string& str) {
	int hash{};

	for (const char& c : str) {
		hash = hash_char(c, hash);
	}

	return hash;
}

int day_15::sum_sequence(const std::vector<std::string>& sequence) {

	auto op = [](int i, const std::string& str) -> int {
		return i + hash_string(str);
		};

	return std::accumulate(sequence.begin(), sequence.end(), 0, op);
}

std::map<int, std::list<day_15::lens>> day_15::fill_boxes(const std::vector<std::string>& sequence) {
	std::map<int, std::list<lens>> boxes;

	for (const std::string& step : sequence) {
		std::string::const_iterator it{ step.begin() };
		std::string id{};
		while (isalpha(*it)) {
			id += *it;
			++it;
		}
		int box = hash_string(id);
		
		auto match_id = [&id](lens l) -> bool {
			return l.label == id;
			};
		
		if (*it == '=') {
			int fl = *++it - '0';
			auto res = std::find_if(boxes[box].begin(), boxes[box].end(), match_id);
			if (res != boxes[box].end()) {
				res->focal_length = fl;
				continue;
			}
			boxes[box].emplace_back(id, fl);
		}
		else {
			boxes[box].remove_if(match_id);
			if (boxes[box].empty()) {
				boxes.erase(box);
			}
		}
	}

	return boxes;
}
	
int day_15::calculate_focal_power(const std::map<int, std::list<lens>>& boxes) {
	
	auto box_power = [](int i, const std::pair<const int, std::list<lens>>& box) {
		auto [B, LENSES] = box;
		
		int lens_count{ 1 };

		for (const lens& L : LENSES) {
			i += (B + 1) * L.focal_length * lens_count;
			++lens_count;
		}

		return i;
		};

	return std::accumulate(boxes.begin(), boxes.end(), 0, box_power);
}