#include "day_05.h"

void day_05::print_answers() {
	std::cout << day_05::DAY_NAME << std::endl;

	auto begin = std::chrono::high_resolution_clock::now();

	std::vector<long long> seeds;
	std::vector<std::pair<long long, long long>> seed_ranges;
	std::vector<std::vector<std::pair<std::pair<long long, long long>, long long>>> range_offsets;
	std::vector<std::vector<std::pair<std::pair<long long, long long>, long long>>> reverse_range_offsets;

	std::vector<std::pair<std::pair<long long, long long>, long long>> map_ranges;
	std::vector<std::pair<std::pair<long long, long long>, long long>> reverse_map_ranges;


	std::ifstream data{ day_05::INPUT_FILE };
	std::string line{};

	auto get_ints_from_string = [](const std::string& str) -> std::vector<long long> {
		std::vector<long long> ints; // reserve sufficient space for long strings
		std::string::const_iterator it{ str.begin() };

		long long n{ -1 };

		while (it != str.end()) {
			if (isdigit(*it)) {
				if (n < 0) {
					n = 0;
				}
				n = n * 10 + (*it - '0');
			}
			else if (n > -1) {
				ints.push_back(n);
				n = -1;
			}
			++it;
		}
		if (n > -1) {
			ints.push_back(n);
		}

		return ints;
		};

	while (data) {
		std::getline(data, line, '\n');
		if (!line.empty()) {
			std::vector<long long> numbers(get_ints_from_string(line));

			if (numbers.size() < 3) {
				continue;
			}

			if (numbers.size() > 3) {
				seeds = numbers;
				for (int i{ 0 }; i < numbers.size(); i += 2) {
					seed_ranges.push_back(std::make_pair(numbers[i], numbers[i] + numbers[i + 1] - 1));
				}
				continue;
			}

			long long destination{ numbers[0] }, source{ numbers[1] }, length{ numbers[2] };
			long long offset{ destination - source };
			std::pair<long long, long long> sub_range{ std::make_pair(source, source + length - 1) };
			map_ranges.push_back(std::make_pair(sub_range, offset));

			std::pair<long long, long long> rev_sub_range{ std::make_pair(destination, destination + length - 1) };
			reverse_map_ranges.push_back(std::make_pair(rev_sub_range, -offset));
		}
		else {
			std::sort(map_ranges.begin(), map_ranges.end());
			range_offsets.push_back(map_ranges);
			map_ranges.clear();
			std::sort(reverse_map_ranges.begin(), reverse_map_ranges.end());
			reverse_range_offsets.push_back(reverse_map_ranges);
			reverse_map_ranges.clear();
		}
	}

	std::reverse(reverse_range_offsets.begin(), reverse_range_offsets.end());

	std::vector<long long> locations(seeds);

	auto convert = [&range_offsets](long long& i) -> void {
		for (const auto& map : range_offsets) {
			for (const auto& [range, offset] : map) {
				if (i < range.first || i > range.second) {
					continue;
				}
				i += offset;
				break;
			}
		}
		};

	std::for_each(locations.begin(), locations.end(), convert);

	long long part_1{ *std::min_element(locations.begin(), locations.end()) };

	std::sort(seed_ranges.begin(), seed_ranges.end());

	long long part_2{ };

	auto find_location_seed = [&reverse_range_offsets](const long long& i) -> long long {
		long long n{ i };
		for (const auto& map : reverse_range_offsets) {
			for (const auto& [range, offset] : map) {
				if (n < range.first || n > range.second) {
					continue;
				}
				n += offset;
				if (n < 0) {
					return -1;
				}
				break;
			}
		}
		return n;
		};

	auto in_seed_range = [&seed_ranges](const long long& i) -> bool {
		for (const auto& [lb, ub] : seed_ranges) {
			if (i < lb || i > ub) {
				continue;
			}
			return true;
		}
		return false;
		};

	/*
	while (!in_seed_range(find_location_seed(part_2))) {
		++part_2;
	}
	*/

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Part 1: " << part_1 << '\n';
	std::cout << "Part 2: " << part_2 << '\n';

	float t = float(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000;

	std::cout << "Time: " << t << " ms\n";



}

