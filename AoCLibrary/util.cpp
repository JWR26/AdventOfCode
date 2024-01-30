#include "util.h"

std::vector<std::string> aoc::split_string(const std::string& str, const char delim) {
	std::vector<std::string> strings;

	size_t first{ 0 }, last{0};

	while ((last = str.find(delim, first)) != std::string::npos) {
		strings.push_back(str.substr(first, last - first));
		first = last + 1;
	}
	
	strings.push_back(str.substr(first));

	return strings;
}

std::vector<std::string> aoc::split_string(const std::string& str, const std::string delim) {
	std::vector<std::string> strings;

	size_t first{ 0 }, last{ 0 };

	while ((last = str.find(delim, first)) != std::string::npos) {
		strings.push_back(str.substr(first, last - first));
		first = last + delim.size();
	}

	strings.push_back(str.substr(first));

	return strings;
}