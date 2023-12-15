#pragma once

#include <vector>



namespace aoc {

	template<typename T>
	class grid {
	private:
		std::vector<T> data;
		size_t rows;
		size_t columns;

	};
}