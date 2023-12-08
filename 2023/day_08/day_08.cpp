#include "day_08.h"

void day_08::print_answers() {
	std::cout << day_08::DAY_NAME << std::endl; 

	std::vector<std::string> input = parser::get_lines(day_08::INPUT_FILE);

	std::queue<char> instructions{ get_instructions(input.front()) };

	std::vector<std::string> map{ input.begin() + 1, input.end() };

	std::map<std::string, std::pair<std::string, std::string>> network{ get_network(map) };

	auto e1_cond = [](const std::string& str) -> bool {
		return str == day_08::END;
		};

	size_t part_1{ count_steps(network, instructions, day_08::START, e1_cond) };

	auto s2_cond = [](const std::string& str) -> bool {
		return str.ends_with('A');
		};

	auto e2_cond = [](const std::string& str) -> bool {
		return str.ends_with('Z');
		};

	size_t part_2{ count_simultaneous_steps(network, instructions, s2_cond, e2_cond) };

	std::cout << "Part 1: " << part_1 << '\n';
	std::cout << "Part 2: " << part_2 << '\n';
	
}

std::queue<char> day_08::get_instructions(const std::string& str) {
	std::queue<char> instructions;
	for (const char& c : str) {
		instructions.emplace(c);
	}
	return instructions;
}

std::map<std::string, std::pair<std::string, std::string>> day_08::get_network(const std::vector<std::string>& map) {
	std::map<std::string, std::pair<std::string, std::string>> network;
	const size_t NODE_LENGTH{ 3 }, LEFT_OFFSET{ 7 }, RIGHT_OFFSET{ 12 };

	for (const std::string& line : map) {
		const std::string NODE{ line.begin(), line.begin() + NODE_LENGTH };
		const std::string LEFT{ line.begin() + LEFT_OFFSET, line.begin() + LEFT_OFFSET + NODE_LENGTH };
		const std::string RIGHT{ line.begin() + RIGHT_OFFSET, line.begin() + RIGHT_OFFSET + NODE_LENGTH };

		network[NODE] = std::make_pair(LEFT, RIGHT);
	}

	return network;
}

size_t day_08::count_steps(const std::map<std::string, std::pair<std::string, std::string>>& network, const std::queue<char>& instructions, const std::string& start, const std::function<bool(std::string)>& end_cond) {
	std::queue<char> q{ instructions };
	std::string current{start};

	size_t steps{};

	while (!end_cond(current)) {
		char i{ q.front() };
		q.pop();
		q.push(i);
		if (i == 'L') {
			current = network.at(current).first;
		}
		else {
			current = network.at(current).second;
		}
		++steps;
	}

	return steps;
}

size_t day_08::count_simultaneous_steps(const std::map<std::string, std::pair<std::string, std::string>>& network, const std::queue<char>& instructions, const std::function<bool(std::string)>& start_cond, const std::function<bool(std::string)>& end_cond) {
	size_t steps{1};

	for (const auto& [node, _] : network) {
		if (!start_cond(node)) {
			continue;
		}
		size_t s{ count_steps(network, instructions, node, end_cond) };
		steps = std::lcm(steps, s);
	}

	return steps;
}