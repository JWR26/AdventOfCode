#include "day_19.h"

void day_19::print_answers() {
	const std::string FILE{ aoc::get_input_file(2023, 19) };
	//const std::string FILE{ aoc::get_test_file(2023, 19) };

	const std::string INPUT{ aoc::read_to_string(FILE) };

	const system WORKFLOWS{ get_workflows(INPUT) };

	const std::vector<part> PARTS{ get_parts(INPUT) };

	const std::vector<part> ACCEPTED{ evaluate_parts(PARTS, WORKFLOWS) };

	auto op = [](int i, part p) -> int {
		return i + get_rating(p);
		};

	int PART_1{ std::accumulate(ACCEPTED.begin(), ACCEPTED.end(), 0, op) };

	const std::vector<range> RANGES{ evaluate_range(WORKFLOWS, 4000) };

	auto op2 = [](size_t i, range r) {
		size_t x{ static_cast<size_t>(r.x.second - r.x.first + 1) };
		size_t m{ static_cast<size_t>(r.m.second - r.m.first + 1) };
		size_t a{ static_cast<size_t>(r.a.second - r.a.first + 1) };
		size_t s{ static_cast<size_t>(r.s.second - r.s.first + 1) };

		return i + (x * m * a * s);
		};

	size_t ZERO{};

	size_t PART_2{ std::accumulate(RANGES.begin(), RANGES.end(), ZERO, op2) };

	aoc::print_answer("--- Day 19: Aplenty ---", PART_1, PART_2);
}

/// <summary>
/// Extracts parts with the format x=..,m=..,a=..,s=.. from a string using regular expressions.
/// </summary>
/// <param name="str">Text to be scanned</param>
/// <returns>A vector of all the found parts</returns>
std::vector<day_19::part> day_19::get_parts(const std::string& str) {
	std::vector<part> parts;

	const std::regex PATTERN{ "x=(\\d+),m=(\\d+),a=(\\d+),s=(\\d+)" };

	std::string::const_iterator start{ str.begin() };
	std::string::const_iterator end{ str.end() };
	std::smatch sm;

	while (std::regex_search(start, end, sm, PATTERN)) {
		int x{ std::stoi(sm[1].str()) };
		int m{ std::stoi(sm[2].str()) };
		int a{ std::stoi(sm[3].str()) };
		int s{ std::stoi(sm[4].str()) };

		parts.emplace_back(x, m, a, s);

		start = sm[0].second;
	}

	return parts;
}

day_19::system day_19::get_workflows(const std::string& str) {
	system workflows;

	const std::regex PATTERN{ "(\\w+)\\{(\\S+)\\}" };

	std::string::const_iterator start{ str.begin() };
	std::string::const_iterator end{ str.end() };
	std::smatch sm;

	while (std::regex_search(start, end, sm, PATTERN)) {
		const std::string WF{ sm[1].str() };

		const std::vector<std::string> INSTRUCTIONS{ aoc::split_string(sm[2].str(), ',')};

		for (const std::string& i : INSTRUCTIONS) {
			if (i == "A" || i == "R" || i.find(':') == std::string::npos) {
				workflows[WF].push_back(rule('x', std::greater<int>(), 0, i));
				continue;
			}
			rule r;
			r.category = i[0];
			if (i[1] == '>') {
				r.comp = std::greater<int>();
			}
			else {
				r.comp = std::less<int>();
			}

			std::string::const_iterator it{ i.begin() + 2 };

			while (*it != ':') {
				r.threshold *= 10;
				r.threshold += *it - '0';
				++it;
			}
			
			++it;

			r.destination = std::string(it, i.end());

			workflows[WF].push_back(r);
		}

		start = sm[0].second;
	}

	return workflows;
}

std::vector<day_19::part> day_19::evaluate_parts(const std::vector<part>& parts, const system& workflows) {
	std::vector<part> accepted;
	accepted.reserve(parts.size());

	for (const part& p : parts) {
		std::string res{ send_to(p, workflows.at("in")) };
		
		while (res != "A" && res != "R") {
			res = send_to(p, workflows.at(res));
		}

		if (res == "A") {
			accepted.push_back(p);
		}
	}

	return accepted;
}

std::string day_19::send_to(const part& p, const std::vector<rule>& rules) {
	for (const rule& r : rules) {
		if (r.comp(p.value.at(r.category), r.threshold)) {
			return r.destination;
		}
	}

	return "";
}

int day_19::get_rating(const part& p) {
	return p.x + p.m + p.a + p.s;
}

std::vector<day_19::range> day_19::evaluate_range(const system& workflows, const int& i) {
	std::vector<range> accepted;
	std::queue<std::pair<range, std::string>> queue;

	queue.push(std::make_pair(range(i), "in"));

	while (!queue.empty()) {
		auto [next, destination] = queue.front();
		queue.pop();

		if (destination == "A") {
			accepted.push_back(next);
			continue;
		}

		if (destination == "R") {
			continue;
		}

		for (const rule& r : workflows.at(destination)) {
			auto [lower, upper] = next.get(r.category);
			bool lower_res{ r.comp(lower, r.threshold) };
			bool upper_res{ r.comp(upper, r.threshold) };

			if (lower_res && upper_res) {
				queue.push(std::make_pair(next, r.destination));
				break;
			}

			if (!lower_res && !upper_res) {
				continue;
			}

			if (lower_res && !upper_res) {
				range split{ next };
				split.set_lower(r.category, r.threshold);
				queue.push(std::make_pair(split, destination));
				next.set_upper(r.category, r.threshold - 1);
				queue.push(std::make_pair(next, r.destination));
				break;
			}

			if (!lower_res && upper_res) {
				range split{ next };
				split.set_upper(r.category, r.threshold);
				queue.push(std::make_pair(split, destination));
				next.set_lower(r.category, r.threshold + 1);
				queue.push(std::make_pair(next, r.destination));
				break;
			}
		}
	}

	return accepted;
}

