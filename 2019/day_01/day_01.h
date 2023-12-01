#pragma once

#include <iostream>
#include <string>

#include "parser.h"

namespace day_01 {
	void print_answers();

	int fuel_for_module(int mass);

	int fuel_for_module_and_fuel(int mass);
}


template<typename T>
T part_one(const std::string& input_file);

template<typename T>
T part_two(const std::string& input_file);
