#pragma once

#include <iostream>
#include <functional>
#include <numeric>
#include <queue>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "input_output.h"
#include "file_parser.h"
#include "util.h"


namespace day_19 {

	struct part {
		int x{}, m{}, a{}, s{};

		std::unordered_map<char, int> value{
			{'x' , x},
			{'m' , m},
			{'a' , a},
			{'s' , s},
		};
	};

	struct range {
		std::pair<int, int> x{}, m{}, a{}, s{};

		range() {}

		range(const int& i) {
			x = std::make_pair(1, i);
			m = std::make_pair(1, i);
			a = std::make_pair(1, i);
			s = std::make_pair(1, i);
		}

		std::pair<int, int> get(const char& c) {
			if (c == 'x') {
				return x;
			}
			if (c == 'm') {
				return m;
			}
			if (c == 'a') {
				return a;
			}
			if (c == 's') {
				return s;
			}
			return std::make_pair(-1, -1);
		}

		void set_lower(const char& c, const int& v) {
			if (c == 'x') {
				x.first = v;
				return;
			}
			if (c == 'm') {
				m.first = v;
				return;
			}
			if (c == 'a') {
				a.first = v;
				return;
			}
			if (c == 's') {
				s.first = v;
				return;
			}
		}

		void set_upper(const char& c, const int& v) {
			if (c == 'x') {
				x.second = v;
				return;
			}
			if (c == 'm') {
				m.second = v;
				return;
			}
			if (c == 'a') {
				a.second = v;
				return;
			}
			if (c == 's') {
				s.second = v;
				return;
			}
		}
	};

	struct rule {
		char category{};
		std::function<bool (int, int)> comp{};
		int threshold{};
		std::string destination{};
	};

	std::vector<part> get_parts(const std::string& str);

	using system = std::unordered_map<std::string, std::vector<rule>>;

	system get_workflows(const std::string& str);

	std::vector<part> evaluate_parts(const std::vector<part>& parts, const system& workflows);

	std::string send_to(const part& p, const std::vector<rule>& rules);

	int get_rating(const part& p);

	std::vector<range> evaluate_range(const system& workflows, const int& i);

	void print_answers();
}

