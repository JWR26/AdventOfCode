#pragma once


#include <iostream>
#include <iterator>
#include <string>
#include <vector>


namespace aoc {

	template<typename T>
	struct grid {
		std::vector<T> _data;
		size_t _rows{}, _columns{};

		grid() {}

		grid(const grid<T>& other) : _data(other.data()), _rows(other.rows()), _columns(other.columns()) {}

		grid(const std::vector<T>& d, const size_t& r, const size_t& c) : _data(d), _rows(r), _columns(c) {}

		grid(const std::vector<std::vector<T>>& nested_vector) {
			_rows = nested_vector.size();
			// assumes all rows are the same length as the first
			_columns = nested_vector.front().size();
			
			for (const std::vector<T>& v : nested_vector) {
				_data.insert(_data.end(), v.begin(), v.end());
			}
		}

		// custom iterators for navigating either a row or a column of the grid
		struct row_iterator {
			using iterator_tag = std::forward_iterator_tag;

			grid<T>* _grid;
			size_t _row{}, _column{};

			row_iterator() = delete; // avoid default construction so _grid can't be "nullptr"

			row_iterator(const row_iterator& other) {
				_grid = other._grid;
				_row = other._row;
				_column = other._column;
			}

			row_iterator(grid* g, const size_t& r) {
				_grid = g;
				_row = r;
			}

			row_iterator(grid* g, const size_t& r, const size_t& c) {
				_grid = g;
				_row = r;
				_column = c;
			}

			T& operator*() const {
				if (_column < _grid->_columns) {
					return *(_grid->_data.begin() + (_row * _grid->_columns + _column));
				}
				return *(_grid->_data.end());
			}

			void operator=(const T& rhs) {
				_grid->data[_row * grid->_columns + _column] = rhs;
			}

			row_iterator operator++() {
				++_column;
				return *this;
			}

			bool operator==(const row_iterator& other) const {
				return (_grid == other._grid && _row == other._row && _column == other._column);
			}

			bool operator!=(const row_iterator& other) const {
				return !(*this == other);
			}
		};

		struct column_iterator {
			using iterator_tag = std::forward_iterator_tag;

			grid<T>* _grid;
			size_t _row{}, _column{};

			column_iterator() = delete; // avoid default construction so _grid can't be "nullptr"

			column_iterator(const column_iterator& other) {
				_grid = other._grid;
				_row = other._row;
				_column = other._column;
			}

			column_iterator(grid* g, const size_t& c) {
				_grid = g;
				_column = c;
			}

			column_iterator(grid* g, const size_t& c, const size_t& r) {
				_grid = g;
				_column = c;
				_row = r;
			}

			T& operator*() const {
				if (_row < _grid->_rows) {
					return *(_grid->_data.begin() + (_row * _grid->_columns + _column));
				}
				return *(_grid->_data.end());
			}

			void operator=(const T& rhs) {
				_grid->data[_row * grid->_columns + _column] = rhs;
			}

			column_iterator operator++() {
				++_row;
				return *this;
			}

			bool operator==(const column_iterator& other) const {
				return (_grid == other._grid && _row == other._row && _column == other._column);
			}

			bool operator!=(const column_iterator& other) const {
				return !(*this == other);
			}
		};

		row_iterator row_begin(const size_t& r) {
			return row_iterator(this, r);
		}

		row_iterator row_end(const size_t& r) {
			return row_iterator(this, r, _columns);
		}

		column_iterator column_begin(const size_t& c) {
			return column_iterator(this, c);
		}

		column_iterator column_end(const size_t& c) {
			return column_iterator(this, c, _rows);
		}

		void operator=(const grid<T>& rhs) {
			_data = rhs._data;
			_rows = rhs._rows;
			_columns = rhs._columns;
		}

		friend std::ostream& operator<<(std::ostream& os, const grid<T>& grid) {
			size_t c_count{1};
			for (const T& t : grid._data) {
				os << t;
				if (c_count > 0 && c_count % grid._columns == 0) {
					os << '\n';
				}
				++c_count;
			}
			return os;
		}
	};
}