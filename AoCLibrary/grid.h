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

		grid(const grid<T>& other) : _data(other._data), _rows(other._rows), _columns(other._columns) {}

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

		struct reverse_row_iterator {
			using iterator_tag = std::forward_iterator_tag;

			grid<T>* _grid;
			size_t _row{}, _column{};

			reverse_row_iterator() = delete; // avoid default construction so _grid can't be "nullptr"

			reverse_row_iterator(const reverse_row_iterator& other) {
				_grid = other._grid;
				_row = other._row;
				_column = other._column;
			}

			reverse_row_iterator(grid* g, const size_t& r) {
				_grid = g;
				_row = r;
				_column = g->_columns - 1;
			}

			reverse_row_iterator(grid* g, const size_t& r, const size_t& c) {
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

			reverse_row_iterator operator++() {
				--_column;
				if (_column > _grid->_columns) {
					_column = _grid->_columns;
				}
				return *this;
			}

			bool operator==(const reverse_row_iterator& other) const {
				return (_grid == other._grid && _row == other._row && _column == other._column);
			}

			bool operator!=(const reverse_row_iterator& other) const {
				return !(*this == other);
			}
		};

		struct reverse_column_iterator {
			using iterator_tag = std::forward_iterator_tag;

			grid<T>* _grid;
			size_t _row{}, _column{};

			reverse_column_iterator() = delete; // avoid default construction so _grid can't be "nullptr"

			reverse_column_iterator(const column_iterator& other) {
				_grid = other._grid;
				_row = other._row;
				_column = other._column;
			}

			reverse_column_iterator(grid* g, const size_t& c) {
				_grid = g;
				_column = c;
				_row = g->_rows - 1;
			}

			reverse_column_iterator(grid* g, const size_t& c, const size_t& r) {
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

			reverse_column_iterator operator++() {
				--_row;
				if (_row > _grid->_rows) {
					_row = _grid->_rows;
				}
				return *this;
			}

			bool operator==(const reverse_column_iterator& other) const {
				return (_grid == other._grid && _row == other._row && _column == other._column);
			}

			bool operator!=(const reverse_column_iterator& other) const {
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

		reverse_row_iterator row_rbegin(const size_t& r) {
			return reverse_row_iterator(this, r);
		}

		reverse_row_iterator row_rend(const size_t& r) {
			return reverse_row_iterator(this, r, _columns);
		}

		reverse_column_iterator column_rbegin(const size_t& c) {
			return reverse_column_iterator(this, c);
		}

		reverse_column_iterator column_rend(const size_t& c) {
			return reverse_column_iterator(this, c, _rows);
		}

		void operator=(const grid<T>& rhs) {
			_data = rhs._data;
			_rows = rhs._rows;
			_columns = rhs._columns;
		}

		bool operator==(const grid<T>& other) const {
			return _data == other._data && _rows == other._rows && _columns == other._columns;
		}

		bool operator!=(const grid<T>& other) const {
			return !(*this == other);
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

namespace std {
	template<>
	struct hash<aoc::grid<char>> {
	public:
		size_t operator()(const aoc::grid<char>& g) const {
			std::string str{ g._data.begin(), g._data.end() };
			return std::hash<std::string>{}(str);
		}
	};
}