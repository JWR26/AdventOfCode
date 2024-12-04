

#include "day_12.h"

void day_12::print_answers() {
	std::cout << DAY_NAME; 

	const std::vector<std::string> INPUT{ aoc::get_lines(INPUT_FILE) };

	ConditionRecords records{ get_records(INPUT) };

	size_t part_1{ sum_records(records) };

	for (auto& rec : records) {
		unfold_record(rec);
	}

	size_t part_2{ sum_records(records) };

	std::cout << "Part 1: " << part_1 << '\n';
	std::cout << "Part 2: " << part_2 << '\n';

}

std::string day_12::get_id(const std::string::iterator& first, const std::string::iterator& last, const size_t& b, const size_t& c) {
	std::string str{ first, last };
	str += '/'; 
	str += std::to_string(b);
	str += '/';
	str += std::to_string(c);
	return str;
}

size_t day_12::possible_arrangements(std::string::iterator first, std::string::iterator last, const std::vector<size_t>& pattern, size_t index, size_t n, Cache& cache) {
	size_t arrangements{};

	// check cache - "have we been here before?"
	std::string current{ get_id(first, last, index, n) };

	if (cache.find(current) != cache.end()) {
		return cache[current];
	}

	const size_t ZERO{ 0 };
	const size_t ONE{ 1 };

	while (first != last) {
		if (*first == DAMAGED) {
			++n;
			// too many consecutive damaged springs
			if (n > pattern[index]) {
				//cache
				cache[current] = ZERO;
				return ZERO;
			}
		}

		if (*first == OPERATIONAL && n > 0) {
			// length of damaged springs does not match pattern
			if (n != pattern[index]) {
				//chache
				cache[current] = ZERO;
				return ZERO;
			}
			++index;
			// got to hitting the end of the pattern
			if (index == pattern.size()) {
				if (std::none_of(first, last, [](char c) {return c == DAMAGED; })) {
					//chache
					cache[current] = ONE;
					return ONE;
				}
				//chache
				cache[current] = ZERO;
				return ZERO;
			}
			n = ZERO;
		}

		if (*first == UNKNOWN) {
			*first = DAMAGED;
			arrangements += possible_arrangements(first, last, pattern, index, n, cache);
			*first = OPERATIONAL;
			arrangements += possible_arrangements(first, last, pattern, index, n, cache);
			*first = UNKNOWN;
			//chache result of decent
			cache[current] = arrangements;
			return arrangements;
		}
		++first;
	}
	// at the last character we should be on last index and have counted the same number of damaged
	if (index == pattern.size() - 1 && n == pattern.back()) {
		//chache
		cache[current] = ONE;
		return ONE;
	}
	//chache
	cache[current] = ZERO;
	return ZERO;
}

size_t day_12::sum_records(const ConditionRecords& records) {
	auto op = [](size_t n, Record r) -> int {
		auto [springs, pattern] = r;
		Cache cache;
		size_t arrangements = possible_arrangements(springs.begin(), springs.end(), pattern, 0, 0, cache);
		return n + arrangements;
		};

	return std::accumulate(records.begin(), records.end(), 0, op);
}

void day_12::unfold_record(Record& record) {
	Record new_record{ record };
	for (int i{ 1 }; i < 5; ++i) {
		new_record.first += UNKNOWN + record.first;
		new_record.second.insert(new_record.second.end(), record.second.begin(), record.second.end());
	}

	record = new_record;
}

day_12::Record day_12::split_record(const std::string& record) {
	const size_t length{ record.find(' ') };
	std::string springs(record, 0, length);

	std::vector<size_t> pattern;
	auto it{ record.begin() + length - 1 };
	size_t n{};

	while (it != record.end()) {
		if (isdigit(*it)) {
			n = n * 10 + (*it - '0');
		}
		else if (n > 0) {
			pattern.emplace_back(n);
			n = 0;
		}
		++it;
	}
	if (n > 0) {
		pattern.emplace_back(n);
	}

	return std::make_pair(springs, pattern);
}

day_12::ConditionRecords day_12::get_records(const std::vector<std::string> record_list) {
	ConditionRecords records;

	for (const std::string& str : record_list) {
		records.emplace_back(split_record(str));
	}

	return records;
}
