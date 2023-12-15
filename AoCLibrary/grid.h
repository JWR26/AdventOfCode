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

		grid(const std::vector<T>& vec, const size_t& r, const size_t& c) : _data(vec), _rows(r), _columns(c) {}

		struct row_iterator {
			using iterator_category = std::forward_iterator_tag;

			row_iterator() {}

			row_iterator(const size_t& r, std::vector<T>::iterator it) {
				row = r;
				col = 0;
				r_it = it + (columns * row);
			}

			row_iterator& operator++() {
				++col;
				if (col < columns) {
					++r_it;
					return *this;
				}
				return data.end();
			}

			T operator*() const {
				return *r_it;
			}

			bool operator==(const row_iterator& other) const {
				return r_it == other.r_it();
			}

			bool operator!=(const row_iterator& other) const {
				return r_it != other.r_it;
			}

		private:
			size_t row{};
			size_t col{};
			std::vector<T>::iterator r_it{};
		};

		struct column_iterator {
			using iterator_category = std::forward_iterator_tag;

			column_iterator() {}

			column_iterator(const size_t& c, std::vector<T>::iterator it) {
				row = 0;
				col = c;
				c_it = it;
			}

			column_iterator& operator++() {
				++row;
				if (row < rows) {
					c_it += columns;
					return *this;
				}
				return data.end();
			}

			T operator*() const {
				return *c_it;
			}

		private:
			size_t row{};
			size_t col{};
			std::vector<T>::iterator c_it{};
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

		_NODISCARD grid<T>::row_iterator row_begin(const size_t& r) const  {
			if (r < _rows) {
				return row_iterator(r, data.begin());
			}
			throw std::out_of_range("Row out of grid range");
		}

		grid<T>::row_iterator row_end(const size_t& r) const {
			return row_iterator(r, data.end());
		}

		grid<T>::column_iterator col_begin(const size_t& c) const  {
			if (c < _columns) {
				return column_iterator(c, data.begin());
			}
			throw std::out_of_range("Column out of grid range");
		}

		grid<T>::column_iterator col_end(const size_t& c) const {
			return column_iterator(c, data.end());
		}
	};
}