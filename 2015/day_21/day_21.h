#pragma once

#include <iostream>
#include <vector>

struct item {
	int cost{};
	int damage{};
	int armour{};

	item(const int& c, const int& d, const int& a) : cost(c), damage(d), armour(a) {}
};

const item DAGGER(8, 4, 0);
const item SHORTSWORD(10, 5, 0);
const item WARHAMMER(25, 6, 0);
const item LONGSWORD(40, 7, 0);
const item GREATAXE(74, 8, 0);

const std::vector<item> WEAPONS({ 
	DAGGER, 
	SHORTSWORD, 
	WARHAMMER, 
	LONGSWORD, 
	GREATAXE
	});

const item NONE(0, 0, 0);
const item LEATHER(13, 0, 1);
const item CHAINMAIL(31, 0, 2);
const item SPLINTMAIL(53, 0, 3);
const item BANDEDMAIL(75, 0, 4);
const item PLATEDMAIL(102, 0, 5);

const std::vector<item> ARMOUR({
	NONE,
	LEATHER,
	CHAINMAIL,
	SPLINTMAIL,
	BANDEDMAIL,
	PLATEDMAIL
	});

const item DAMAGE_ONE(25, 1, 0);
const item DAMAGE_TWO(50, 2, 0);
const item DAMAGE_THREE(100, 3, 0);
const item DEFENSE_ONE(20, 0, 1);
const item DEFENSE_TWO(40, 0, 2);
const item DEFENSE_THREE(80, 0, 3);

const std::vector<item> RINGS({
	NONE,
	NONE,
	DAMAGE_ONE,
	DAMAGE_TWO,
	DAMAGE_THREE,
	DEFENSE_ONE,
	DEFENSE_TWO,
	DEFENSE_THREE});

struct player {
	item weapon;
	item armour{ NONE };
	item ring_right{ NONE };
	item ring_left{ NONE };

	int get_cost() const {
		return weapon.cost + armour.cost + ring_right.cost + ring_left.cost;
	}
};

namespace day_21 {
	void print_answers();

	int part_one(const std::string& input_file);
	int part_two(const std::string& input_file);
}