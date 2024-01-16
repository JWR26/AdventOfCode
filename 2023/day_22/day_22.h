#pragma once

#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "input_output.h"
#include "file_parser.h"

namespace day_22 {

	void print_answers();

	struct brick {
		int x{}, y{}, z{};
		int length{}, width{}, height{};

		std::vector<brick> supported_by{}, supporting{};

		bool operator==(const brick& other) const {
			return (x == other.x) && (y == other.y) && (z == other.z) && (length == other.length) && (width == other.width) && (height == other.height);
		}

		brick& operator=(const brick& other) {
			x = other.x;
			y = other.y;
			z = other.z;
			length = other.length;
			width = other.width;
			height = other.height;
			return *this;
		}
	};

	std::vector<brick> get_bricks(const std::string& str);

	bool compare_z(const brick& b1, const brick& b2);

	std::vector<brick>& fall(std::vector<brick>& snapshot);

	std::vector<brick>& establish_supports(std::vector<brick>& stack);

	std::vector<brick> disintegrate(const std::vector<brick>& stack);
}