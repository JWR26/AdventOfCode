#include "day_04.h"

std::vector<std::pair<std::set<int>, std::set<int>>> parse_cards(const std::string& file_path) {
	std::ifstream data{ file_path };
	
	std::vector<std::pair<std::set<int>, std::set<int>>> scratchcards;
	std::string line{};
	std::string::iterator it;
	int n{};
	
	std::set<int> winning_numbers;
	std::set<int> card_numbers;

	auto evaluate_char = [&](std::set<int>& container, const char& c) -> void {
		if (isdigit(c)) {
			n = n * 10 + (c - '0');
		}
		else if (n > 0) {
			container.insert(n);
			n = 0;
		}
		++it;
		};

	while (data) {
		std::getline(data, line, '\n');
		if (!line.empty()) {
			it = line.begin();
			while (*it != ':') {
				++it;
			}
			while (*it != '|') {
				evaluate_char(winning_numbers, *it);
			}
			while (it != line.end()) {
				evaluate_char(card_numbers, *it);
			}
			if (n > 0) {
				card_numbers.insert(n);
				n = 0;
			}
			scratchcards.push_back(std::make_pair(winning_numbers, card_numbers));
			winning_numbers.clear();
			card_numbers.clear();
			n = 0;
		}
	}
	return scratchcards;
}

void day_04::print_answers() {
	std::cout << day_04::DAY_NAME << '\n';

	std::vector<std::pair<std::set<int>, std::set<int>>> scratchcards(parse_cards(day_04::INPUT_FILE));

	std::map<int, int> card_totals;
	std::vector<int> matches;
	std::queue<int> copies;

	int pile_worth{}, index{}, copy_index{}, total_cards{};

	for (const auto& [wn, cn] : scratchcards) {
		card_totals[index] += 1;
		std::set_intersection(wn.begin(), wn.end(), cn.begin(), cn.end(), std::back_inserter(matches));
		if (matches.size() > 0) {
			pile_worth += pow(2, matches.size() - 1);
			copy_index = index + matches.size() + 1;
			for (int i{ index + 1 }; i < copy_index; ++i) {
				card_totals[i] += card_totals[index];
			}
		}
		matches.clear();
		total_cards += card_totals[index];
		++index;
	}

	std::cout << "Part 1: " << pile_worth << '\n';

	std::cout << "Part 2: " << total_cards << '\n';
}

int day_04::part_two(const std::string& input_file) {
	int answer{};
	return answer;
}
