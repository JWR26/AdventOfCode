#include "day_13.h"

void day_13::print_answers() {
	std::cout << DAY_NAME; 

	const std::vector<std::vector<std::string>> INPUT{ file_parser::get_paragraphs(INPUT_FILE) };

	int part_1{ summarise_notes(INPUT) };

	std::cout << "Part 1: " << part_1 << '\n';

}

int day_13::find_reflection_line(std::vector<std::string>::const_iterator first, std::vector<std::string>::const_iterator last) {

	std::vector<std::string>::const_iterator next{ std::adjacent_find(first, last) };

	while (next != last) {
		// found two consecutive matching strings check for mirror line

		// mirror line if the "bottom" reaches the end before the top reaches the beginning
		std::vector<std::string>::const_iterator top{ next };
		std::vector<std::string>::const_iterator bottom{ top + 1 };


		while (top != first && bottom != last) {
			if (*top != *bottom) {
				break; // not a mirror line
			}
			// move the top and bottom one line a part
			--top;
			++bottom;
			// if the bottom is the end of the vector, found the mirror line
			if (bottom == last) {
				return std::distance(first, next + 1); // plus one to take "far column" of mirror line
			}
		}
		// if the top is first and equal to the bottom, mirror line found
		if (top == first && *top == *bottom) {
			return std::distance(first, next + 1);
		}

		next = std::adjacent_find(++next, last);
	}

	// return 0 if no mirror line is found
	return 0;
}

std::vector<std::string> day_13::transpose(const std::vector<std::string>& rows) {
	std::vector<std::string> transposed{ rows.front().size() };

	for (const auto& r : rows) {
		for (int i{ 0 }; i < r.size(); ++i) {
			transposed[i] += r[i];
		}
	}

	return transposed;
}

int day_13::reflection_line_score(const std::vector<std::string>& pattern) {
	int score{ find_reflection_line(pattern.begin(), pattern.end()) };
	// horizontal reflection
	if (score != 0) {
		return score * 100;
	}

	// vertical reflection
	std::vector<std::string> transposed{ transpose(pattern) };
	score = find_reflection_line(transposed.begin(), transposed.end());
	return score;
}

int day_13::summarise_notes(const std::vector<std::vector<std::string>>& notes) {
	auto op = [](int i, std::vector<std::string> n) -> int {
		return i + reflection_line_score(n);
		};

	return std::accumulate(notes.begin(), notes.end(), 0, op);
}

std::string::iterator day_13::single_mismatch(std::string& a, std::string& b) {
	auto [a_first, b_first] = std::mismatch(a.begin(), a.end(), b.begin(), b.end());
	// lines are identical
	if (a_first == a.end()) {
		return a.end();
	}

	auto [a_second, b_second] = std::mismatch(a_first + 1, a.end(), b_first + 1, b.end());
	// if single mismatch return true with the index
	if (a_second == a.end()) {
		return a_first;
	}
	return a.end();
}

