#include "day_04.h"

std::vector<std::pair<std::set<int>, std::set<int>>> day_04::parse_cards(const std::string& file_path) {
	std::ifstream data{ file_path };
	std::vector<std::pair<std::set<int>, std::set<int>>> scratchcards;
	std::string line{};

	while (data) {
		std::getline(data, line, '\n');
		if (!line.empty()) {
			std::string::iterator it{ line.begin() };
			std::set<int> winning_numbers;
			std::set<int> card_numbers;
			int n{};

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
			n = 0;
		}
	}
	return scratchcards;
}

long long first_optimise(const std::string& file_path) {
	auto begin = std::chrono::high_resolution_clock::now();

	std::ifstream data{ file_path };
	std::vector<std::pair<std::set<int>, std::set<int>>> scratchcards;
	std::string line{};

	int pile_worth{}, index{}, total_cards{};

	std::vector<int> card_totals(220, 1);

	while (data) {
		std::getline(data, line, '\n');
		if (!line.empty()) {
			std::string::iterator it{ line.begin() };
			std::set<int> winning_numbers;
			std::set<int> card_numbers;
			int n{};

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
			}

			std::vector<int> matches;
			std::set_intersection(winning_numbers.begin(), winning_numbers.end(), card_numbers.begin(), card_numbers.end(), std::back_inserter(matches));
			if (matches.size() > 0) {
				pile_worth += pow(2, matches.size() - 1);
				for (int i{ index + 1 }; i < index + matches.size() + 1; ++i) {
					card_totals[i] += card_totals[index];
				}
			}
			total_cards += card_totals[index];
			++index;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();

	auto t = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

	return t;
}

long long second_optimise(const std::string& file_path) {
	auto begin = std::chrono::high_resolution_clock::now();

	std::ifstream data{ file_path };
	std::vector<std::pair<std::vector<int>, std::vector<int>>> scratchcards;
	std::string line{};

	int pile_worth{}, index{}, total_cards{};

	std::vector<int> card_totals(220, 1);

	while (data) {
		std::getline(data, line, '\n');
		if (!line.empty()) {
			std::string::iterator it{ line.begin() };
			std::vector<int> winning_numbers;
			std::vector<int> card_numbers;
			int n{};

			auto evaluate_char = [&](std::vector<int>& container, const char& c) -> void {
				if (isdigit(c)) {
					n = n * 10 + (c - '0');
				}
				else if (n > 0) {
					container.push_back(n);
					n = 0;
				}
				++it;
				};

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
				card_numbers.push_back(n);
			}

			std::sort(winning_numbers.begin(), winning_numbers.end());
			std::sort(card_numbers.begin(), card_numbers.end());

			std::vector<int> matches;
			std::set_intersection(winning_numbers.begin(), winning_numbers.end(), card_numbers.begin(), card_numbers.end(), std::back_inserter(matches));
			if (matches.size() > 0) {
				pile_worth += pow(2, matches.size() - 1);
				for (int i{ index + 1 }; i < index + matches.size() + 1; ++i) {
					card_totals[i] += card_totals[index];
				}
			}
			total_cards += card_totals[index];
			++index;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();

	auto t = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

	return t;
}

long long third_optimise(const std::string& file_path) {
	auto begin = std::chrono::high_resolution_clock::now();

	std::ifstream data{ file_path };
	std::string line{};

	int pile_worth{}, index{}, total_cards{};

	std::vector<int> card_totals(220, 1);

	while (data) {
		std::getline(data, line, '\n');
		if (!line.empty()) {
			std::string::iterator it{ line.begin() };
			std::vector<bool> winning_numbers(100, false);
			int n{};
			int wins{};

			while (*it != ':') {
				++it;
			}
			while (*it != '|') {
				if (isdigit(*it)) {
					n = n * 10 + (*it - '0');
				}
				else if (n > 0) {
					winning_numbers[n] = true;
					n = 0;
				}
				++it;
			}
			while (it != line.end()) {
				if (isdigit(*it)) {
					n = n * 10 + (*it - '0');
				}
				else if (n > 0) {
					if (winning_numbers[n]) {
						++wins;
					}
					n = 0;
				}
				++it;
			}
			if (n > 0) {
				if (winning_numbers[n]) {
					++wins;
				}
			}
			if (wins > 0) {
				pile_worth += pow(2, wins - 1);
				for (int i{ index + 1 }; i < index + wins + 1; ++i) {
					card_totals[i] += card_totals[index];
				}
			}
			
			total_cards += card_totals[index];
			++index;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();

	auto t = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

	return t;
}

long long fourth_optimise(const std::string& file_path)  {
	
	std::ifstream data{ file_path };

	auto begin = std::chrono::high_resolution_clock::now();

	std::string line{};

	int pile_worth{}, index{}, total_cards{};

	std::vector<int> card_totals(220, 1);

	while (data) {
		std::getline(data, line, '\n');
		if (!line.empty()) {
			std::string::iterator it{ line.begin() };
			std::bitset<100> winning_numbers;
			int n{};
			int wins{};

			while (*it != ':') {
				++it;
			}
			while (*it != '|') {
				if (isdigit(*it)) {
					n = n * 10 + (*it - '0');
				}
				else if (n > 0) {
					winning_numbers[n] = true;
					n = 0;
				}
				++it;
			}
			while (it != line.end()) {
				if (isdigit(*it)) {
					n = n * 10 + (*it - '0');
				}
				else if (n > 0) {
					if (winning_numbers[n]) {
						++wins;
					}
					n = 0;
				}
				++it;
			}
			if (n > 0) {
				if (winning_numbers[n]) {
					++wins;
				}
			}
			if (wins > 0) {
				pile_worth += pow(2, wins - 1);
				for (int i{ index + 1 }; i < index + wins + 1; ++i) {
					card_totals[i] += card_totals[index];
				}
			}

			total_cards += card_totals[index];
			++index;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();

	auto t = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

	return t;
}

void day_04::print_answers() {
	std::cout << day_04::DAY_NAME << '\n';

	auto begin = std::chrono::high_resolution_clock::now();

	const std::vector<std::pair<std::set<int>, std::set<int>>> SCRATCHCARDS(parse_cards(day_04::INPUT_FILE));

	auto parse_time = std::chrono::high_resolution_clock::now();

	std::vector<int> card_totals(SCRATCHCARDS.size(), 1);
	
	int pile_worth{}, index{}, total_cards{};

	for (const auto& [wn, cn] : SCRATCHCARDS) {
		std::vector<int> matches;
		std::set_intersection(wn.begin(), wn.end(), cn.begin(), cn.end(), std::back_inserter(matches));
		if (matches.size() > 0) {
			pile_worth += pow(2, matches.size() - 1);
			for (int i{ index + 1 }; i < index + matches.size() + 1; ++i) {
				card_totals[i] += card_totals[index];
			}
		}
		total_cards += card_totals[index];
		++index;
	}

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Part 1: " << pile_worth << '\n';

	std::cout << "Part 2: " << total_cards << '\n';

	float t = float(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000;

	std::cout << "Time: " << t << " ms\n";
	
	std::vector<float> averages(5, 0.0);

	const int ITERATIONS{ 1 };

	for (int i{ 0 }; i < ITERATIONS; ++i) {
		averages[0] += float(first_optimise(day_04::INPUT_FILE)) / 1000;
		averages[1] += float(second_optimise(day_04::INPUT_FILE)) / 1000;
		averages[2] += float(third_optimise(day_04::INPUT_FILE)) / 1000;
		averages[3] += float(fourth_optimise(day_04::INPUT_FILE)) / 1000;
	}

	for (float& a : averages) {
		a /= ITERATIONS;
	}

	std::cout << "\nOptimise by evaluating cards during parse:\n    Average Time:  " << averages[0] << "ms\n    x" << 1.0 / (averages[0] / t) << " faster\n";
	std::cout << "\nOptimise by using vectors instead of sets:\n    Average Time:  " << averages[1] << "ms\n    x" << 1.0 / (averages[1] / t) << " faster\n";
	std::cout << "\nOptimise by using a vector<bool> to mark winning numbers:\n    Average Time:  " << averages[2] << "ms\n    x" << 1.0 / (averages[2] / t) << " faster\n";
	std::cout << "\nOptimise by using std::bitset instead of vector<bool>:\n    Average Time: " << averages[3] << "ms\n    x" << 1.0 / (averages[3] / t) << " faster\n\n";
}