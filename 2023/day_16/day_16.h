#pragma once

#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>

#include "file_parser.h"

namespace day_16 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_16\\input.txt" };
	const std::string DAY_NAME{ "--- Day 16: The Floor Will Be Lava ---\n" };

	const char H_SPLIT{ '|' };
	const char V_SPLIT{ '-' };
	const char L_MIRROR{ '\\' };
	const char R_MIRROR{ '/' };

	enum DIRECTION {
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

	using MirrorResult = std::unordered_map<char, std::unordered_map<DIRECTION, DIRECTION>>;

	const MirrorResult MIRROR{
		{ L_MIRROR, {
			{ DIRECTION::RIGHT, DIRECTION::DOWN },
			{ DIRECTION::DOWN, DIRECTION::RIGHT },
			{ DIRECTION::LEFT, DIRECTION::UP },
			{ DIRECTION::UP, DIRECTION::LEFT },
			}
		},
		{ R_MIRROR , {
			{ DIRECTION::RIGHT, DIRECTION::UP },
			{ DIRECTION::UP, DIRECTION::RIGHT },
			{ DIRECTION::LEFT, DIRECTION::DOWN },
			{ DIRECTION::DOWN, DIRECTION::LEFT },
			}
		},
	};

	using CanSplit = std::unordered_map<char, std::unordered_map<DIRECTION, bool>>;

	const CanSplit CAN_SPLIT{
		{ H_SPLIT, {
			{ DIRECTION::UP, false },
			{ DIRECTION::DOWN, false },
			{ DIRECTION::LEFT, true },
			{ DIRECTION::RIGHT, true },
			}
		},
		{ V_SPLIT, {
			{ DIRECTION::UP, true },
			{ DIRECTION::DOWN, true },
			{ DIRECTION::LEFT, false },
			{ DIRECTION::RIGHT, false },
			}
		},
	};

	using SplitResult = std::unordered_map<DIRECTION, std::pair<DIRECTION, DIRECTION>>;

	const SplitResult SPLIT{
		{DIRECTION::UP, std::make_pair(DIRECTION::LEFT, DIRECTION::RIGHT)},
		{DIRECTION::DOWN, std::make_pair(DIRECTION::LEFT, DIRECTION::RIGHT)},
		{DIRECTION::LEFT, std::make_pair(DIRECTION::UP, DIRECTION::DOWN)},
		{DIRECTION::RIGHT, std::make_pair(DIRECTION::UP, DIRECTION::DOWN)},
	};

	struct grid {
		const std::vector<char> DATA;
		const int ROWS{}, COLUMNS{};

		grid(const std::vector<char>& data, const int& rows, const int& columns ) : DATA(data), ROWS(rows), COLUMNS(columns) {}
	};

	struct beam {
		int row{}, column{};
		DIRECTION direction{ DIRECTION::RIGHT };
	};

	bool on_grid(const grid& g, const beam& b);

	void update_beam(beam& b);

	void print_answers();

	std::vector<bool> bounce_beam(const grid& g, const beam& start);

	grid get_grid(const std::vector<std::vector<char>>& input);

	int tiles_energised(const grid& g, const beam& b);

	int largest_energisation(const grid& g);
}
