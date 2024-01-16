#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
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
		std::string id{};

		int x{}, y{}, z{};
		int length{}, width{}, height{};

		std::vector<brick> supported_by{}, supporting{};

		bool operator==(const brick& other) const {
			return (id == other.id) && (x == other.x) && (y == other.y) && (z == other.z) && (length == other.length) && (width == other.width) && (height == other.height);
		}

		brick& operator=(const brick& other) {
			id = other.id;
			x = other.x;
			y = other.y;
			z = other.z;
			length = other.length;
			width = other.width;
			height = other.height;
			supported_by = other.supported_by;
			supporting = other.supporting;
			return *this;
		}
	};

	std::vector<brick> get_bricks(const std::string& str);

	bool compare_z(const brick& b1, const brick& b2);

	std::vector<brick>& fall(std::vector<brick>& snapshot);

	std::vector<brick> disintegrate(const std::vector<brick>& stack);

	int chain_reaction(const std::vector<brick>& stack, const brick& start);

	int sum_chain_reactions(const std::vector<brick>& stack, const std::vector<brick>& brick_list);
}