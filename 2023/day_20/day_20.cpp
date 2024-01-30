#include "day_20.h"

void day_20::print_answers() {
	const std::string FILE{ aoc::get_input_file(2023, 20) };
	//const std::string FILE{ aoc::get_test_file(2023, 20) };
	//const std::string FILE{ aoc::get_test_file(2023, 20, 'b') };

	const std::vector<std::string> INPUT{ aoc::get_lines(FILE) };

	module_map modules{ get_modules(INPUT) };
	
	set_conjunction_inputs(modules);

	const int PART_1{warm_up(modules, 1000)};

	const int PART_2{};

	aoc::print_answer("--- Day 20: Pulse Propagation ---", PART_1, PART_2);
}

day_20::PULSE day_20::module::receive(const PULSE& p, const std::string& from) {
	return p;
}

day_20::PULSE day_20::flip_flop::receive(const PULSE& p, const std::string& from) {
	if (p == PULSE::HIGH) {
		return PULSE::NONE;
	}

	on = !on;

	if (on) {
		return PULSE::HIGH;
	}

	return PULSE::LOW;
}

day_20::PULSE day_20::conjunction::receive(const PULSE& p, const std::string& from) {
	last_pulse[from] = p;

	if (std::all_of(last_pulse.begin(), last_pulse.end(), [](std::pair<std::string, PULSE> last) {return last.second == PULSE::HIGH; })) {
		return PULSE::LOW;
	}

	return PULSE::HIGH	;
}

day_20::module_map day_20::get_modules(const std::vector<std::string>& input) {
	module_map modules;

	for (const std::string& str : input) {
		size_t pos{ str.find(" -> ") };
		std::string prefix{ str.substr(0, pos) };
		std::string suffix{ str.substr(pos + 4) };
		
		if (prefix == "broadcaster") {
			modules[prefix] = std::make_unique<module>();
			modules[prefix]->destination_modules = aoc::split_string(suffix, ", ");
		}

		if (prefix[0] == '%') {
			std::string id{ prefix.begin() + 1, prefix.end() };
			modules[id] = std::make_unique<flip_flop>();
			modules[id]->destination_modules = aoc::split_string(suffix, ", ");
		}
		
		if (prefix[0] == '&') {
			std::string id{ prefix.begin() + 1, prefix.end() };
			modules[id] = std::make_unique<conjunction>();
			modules[id]->destination_modules = aoc::split_string(suffix, ", ");
		}

	}

	return modules;
}

void day_20::set_conjunction_inputs(module_map& configuration) {
	for (auto& [str, mod] : configuration) {
		for (const std::string& next : mod->destination_modules) {
			if (configuration.find(next) == configuration.end()) {
				continue;
			}

			conjunction* res{ dynamic_cast<conjunction*>(configuration[next].get()) };
			
			if (res) {
				res->last_pulse[str] = PULSE::LOW;
			}
		}
	}

}

std::pair<int, int> day_20::push_button(module_map& configuration) {
	int high{}, low{};

	std::queue<send_pulse> queue;

	queue.push(send_pulse("button", "broadcaster", PULSE::LOW));

	while (!queue.empty()) {
		auto [from, to, type] = queue.front();
		queue.pop();

		if (type == PULSE::HIGH) {
			++high;
		}
		else {
			++low;
		}

		if (configuration.find(to) == configuration.end()) {
			continue;
		}

		PULSE p{ configuration[to]->receive(type, from) };

		if (p == PULSE::NONE) {
			continue;
		}

		for (const std::string& str : configuration[to]->destination_modules) {
			queue.push(send_pulse(to, str, p));
		}
	}

	return std::make_pair(high, low);
}

int day_20::warm_up(module_map& configuration, int pushes) {
	int high{}, low{};

	while (pushes > 0) {
		std::pair<int, int> res{ push_button(configuration) };
		high += res.first;
		low += res.second;
		--pushes;
	}

	return high * low;
}
