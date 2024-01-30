#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "input_output.h"
#include "file_parser.h"
#include "util.h"

namespace day_20 {
	
	enum PULSE {
		LOW,
		HIGH,
		NONE,
	};
	
	struct module {
		std::vector<std::string> destination_modules;

		virtual PULSE receive(const PULSE& p, const std::string& from);
	};

	struct flip_flop : module {
		bool on{ false };

		PULSE receive(const PULSE& p, const std::string& from);
	};

	struct conjunction : module {
		std::unordered_map<std::string, PULSE> last_pulse;

		PULSE receive(const PULSE& p, const std::string& from);
	};

	struct send_pulse {
		const std::string FROM;
		const std::string TO;
		const PULSE PULSE_TYPE;
	};

	using module_map = std::unordered_map<std::string, std::unique_ptr<module>>;

	module_map get_modules(const std::vector<std::string>& input);

	void set_conjunction_inputs(module_map& configuration);

	std::pair<int, int> push_button(module_map& configuration);

	int warm_up(module_map& configuration, int pushes);

	void print_answers();
}
