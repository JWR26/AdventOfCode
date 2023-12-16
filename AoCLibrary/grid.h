#pragma once

#include <stdexcept>
#include <vector>



namespace aoc {

	template<typename T>
	class grid {
	private:
		std::vector<T> _data;
		size_t _rows;
		size_t _columns;

	public:
		grid(){}

		grid(const std::vector<T>& vec, const size_t& r, const size_t& c) {
			if (vec.size() != (r * c)) {
				throw std::invalid_argument("Data size does not match required grid size");
			}

			_data = vec;
			_rows = r;
			_columns = c;
		}

		struct row_iterator {

			row_iterator(const size_t row) : _r(row) {}

			std::vector<T>::iterator operator++() {
				++_c;
				if (_c < _columns) {
					return _data.begin() + (_r * _columns + _c);
				}
				return _data.end();
			}

			std::vector<T>::iterator operator*() {
				return _data.begin() + (_r * _columns + _c);
			}

		private:
			size_t _r{}, _c{};
		};
		
		size_t columns() const {
			return _columns;
		}

		size_t rows() const {
			return _rows;
		}

		size_t size() const {
			return _data.size();
		}

		std::vector<T>::iterator row_begin(const size_t& row) {
			return *row_iterator(row);
		}


	};
}