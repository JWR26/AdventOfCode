#pragma once

#include <string>
#include <vector>

namespace aoc {

	std::vector<std::string> split_string(const std::string& str, const char delim);

	std::vector<std::string> split_string(const std::string& str, const std::string delim);
}