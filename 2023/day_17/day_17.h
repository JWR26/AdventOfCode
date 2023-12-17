#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "file_parser.h"

namespace day_17 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_17\\input.txt" };
	const std::string DAY_NAME{ "--- Day 17: Clumsy Crucible ---\n" };

	const int MAX_CRUCIBLE{ 3 };
	const int MIN_ULTRA{ 4 };
	const int MAX_ULTRA{ 10 };

	void print_answers();

	enum DIRECTION {
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

	// key is current direction, values are possible directions after turning
	const std::unordered_map < DIRECTION, std::vector < DIRECTION >> TURN_DIRECTIONS{
		{DIRECTION::LEFT, {DIRECTION::UP, DIRECTION::DOWN}},
		{DIRECTION::RIGHT, {DIRECTION::UP, DIRECTION::DOWN}},
		{DIRECTION::UP, {DIRECTION::RIGHT, DIRECTION::LEFT}},
		{DIRECTION::DOWN, {DIRECTION::RIGHT, DIRECTION::LEFT}},
	};

	struct grid {

		std::vector<int> DATA;
		size_t ROWS{}, COLUMNS{};
		
		grid() {}

		grid(const std::vector<int>& data, const size_t& rows, const size_t& columns) : DATA(data), ROWS(rows), COLUMNS(columns) {}

	};

	struct crucible {
		grid g; // reference grid the crucible is on -> good for hashing
		size_t row{}, column{};
		DIRECTION direction{ DIRECTION::RIGHT };
		int consecutive_moves{};
		int64_t heat_loss{};

		crucible() {}

		crucible(const grid& _g, const size_t& r, const size_t& c, const DIRECTION& d, const int& cm, const int64_t h) : g(_g), row(r), column(c), direction(d), consecutive_moves(cm), heat_loss(h) {}

		bool operator==(const crucible& other) const {
			return (row == other.row && column == other.column && direction == other.direction);
		}

		bool operator<(const crucible& other) const {
			return heat_loss < other.heat_loss;
		}

		bool operator>(const crucible& other) const {
			return heat_loss > other.heat_loss;
		}

		crucible& operator=(const crucible& other) {
			if (this == &other) {
				return *this;
			}
			g = other.g;
			row = other.row;
			column = other.column;
			direction = other.direction;
			consecutive_moves = other.consecutive_moves;
			heat_loss = other.heat_loss;

			return *this;
		}
	};

	using visited_blocks = std::unordered_map<crucible, crucible>;

	bool on_grid(const grid& g, const crucible& c);

	void update_crucible(crucible& c);

	grid get_grid(const std::vector<std::vector<char>>& input);

	int64_t find_min_heat_loss(const grid& g, const int& min_turn, const int& max_straight);
}


// customisation of the std::hash template for crucibles.
// a crucible is identified by its position on the grid. Direction * grid size is to allow the same row & column to exist in each direction
namespace std {
	template<>
	struct hash<day_17::crucible> {
	public:
		size_t operator()(const day_17::crucible& c) const {
			return c.row * c.g.COLUMNS + c.column + (c.direction * c.g.DATA.size());
		}
	};
}