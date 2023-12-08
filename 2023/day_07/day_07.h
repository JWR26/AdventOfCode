#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "file_parser.h"

namespace day_07 {
	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_07\\input.txt" };
	const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_07\\test.txt" };
	const std::string DAY_NAME{ "--- Day 7: Camel Cards ---" };

	const std::unordered_map<char, char> CARD_VALUES{
		{'2', 'b'},
		{'3', 'c'},
		{'4', 'd'},
		{'5', 'e'},
		{'6', 'f'},
		{'7', 'g'},
		{'8', 'h'},
		{'9', 'i'},
		{'T', 'j'},
		{'J', 'k'},
		{'Q', 'l'},
		{'K', 'm'},
		{'A', 'n'},
	};

	class Hand {
		enum TYPE {
			HIGH_CARD,
			PAIR,
			TWO_PAIR,
			THREE,
			FULL,
			FOUR,
			FIVE,
		};
	private:
		std::string hand{};
		std::string values{};
		
		TYPE type{ HIGH_CARD }; // default to high card
		int bid{};

		void set_type() {
			std::string temp{ hand };
			std::sort(temp.begin(), temp.end());
			TYPE t{ HIGH_CARD };
			int duplicates{};
			char prev{};
			for (const char& c : temp) {
				if (c == prev) {
					++duplicates;
				}
				else {
					duplicates = 0;
				}

				if (duplicates > 3) {
					t = TYPE::FIVE;
				}
				else if (duplicates > 2) {
					t = TYPE::FOUR;
				}
				else if (duplicates > 1) {
					if (t == TYPE::THREE || t == TYPE::TWO_PAIR) {
						t = TYPE::FULL;
					} 
					else {
						t = TYPE::THREE;
					}
				}
				else if (duplicates > 0) {
					if (t == TYPE::THREE) {
						t = TYPE::FULL;
					}
					else if (t == TYPE::PAIR) {
						t = TYPE::TWO_PAIR;
					}
					else {
						t = TYPE::PAIR;
					}
				}
				prev = c;
			}
			type = t;
		}

	public:
		Hand(){}

		Hand(const std::string& str) {
			std::string::const_iterator str_it{ str.begin() };
			while (*str_it != ' ') {
				hand += *str_it;
				values += CARD_VALUES.at(*str_it);
				++str_it;
			}
			++str_it; // move over space...
			while (str_it != str.end()) {
				bid = bid * 10 + (*str_it - '0');
				++str_it;
			}
			set_type();
		}

		// part two -> function to adapt type the the best possible hand
		void apply_joker() {
			std::replace(values.begin(), values.end(), CARD_VALUES.at('J'), 'a');
			// guard against no J case
			if (hand.find('J') == std::string::npos) {
				return;
			}
			// guard against "JJJJJ" case
			if (hand == "JJJJJ") {
				return;
			}

			std::string temp{ hand };
			std::sort(temp.begin(), temp.end());
			std::vector<Hand> possible_hands;
			possible_hands.reserve(hand.size());;
			char prev{};
			for (const char& c : temp) {
				if (c == prev || c == 'J') {
					continue;
				}
				std::string s{ hand };
				std::replace(s.begin(), s.end(), 'J', c);
				s += " 0"; // add the 0 for the bid
				possible_hands.emplace_back(s);
			}

			std::sort(possible_hands.begin(), possible_hands.end());
			type = possible_hands.back().get_type();
		}

		int get_bid() const {
			return bid;
		}

		// part 2 -> alows overwite of a hand type by another
		TYPE get_type() const{
			return type;
		}

		friend bool operator< (const Hand& lhs, const Hand& rhs) {
			if (lhs.type == rhs.type) {
				return lhs.values < rhs.values;
			}
			return lhs.type < rhs.type;
		}
	};

	std::vector<Hand> get_hands(const std::vector<std::string>& strings);

	template<typename T = int>
	T determine_winnings(const std::vector<Hand>& hands) {
		// required hands to be sorted
		T multiplier{ 1 };
		auto hand_winnings = [&multiplier](T n, Hand h) -> T {
			n += h.get_bid() * multiplier;
			++multiplier;
			return n;
			};

		return std::accumulate(hands.begin(), hands.end(), 0, hand_winnings);
	}

	void print_answers();

	int part_one(const std::string& input_file);

	int part_two(const std::string& input_file);
}
