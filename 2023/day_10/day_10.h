#pragma once

#include <iostream>
#include <map>
#include <stack>
#include <unordered_set>
#include <vector>

#include "file_parser.h"
#include "graph.h"

namespace day_10 {
	
	template<typename T = char>
	using grid = std::vector<std::vector<T>>;

	const std::string INPUT_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_10\\testa.txt" };
	const std::string DOUG_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_10\\doug_input.txt" };
	const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_10\\teste.txt" };
	const std::string DAY_NAME{ "--- Day 10: Pipe Maze ----\n" };

	void print_answers();

	template<typename T = char>
	graph::unweighted<T> build_graph(const grid<T>& g) {
		// declare constants 
		const int MAX_ROW{ static_cast<int>(g.size()) };
		const int MAX_COL{ static_cast<int>(g.front().size())};

		const std::map<char, std::vector<std::pair<int, int>>> PIPE_NEIGHBOURS{
			{'|', {std::make_pair(-1, 0), std::make_pair(1, 0)}}, // vertical pipe N & S
			{'-', {std::make_pair(0, 1), std::make_pair(0, -1)}}, // horizontal pipe E & W
			{'L', {std::make_pair(-1, 0), std::make_pair(0, 1)}}, // N & E
			{'J', {std::make_pair(-1, 0), std::make_pair(0, -1)}}, // N & W
			{'7', {std::make_pair(1, 0), std::make_pair(0, -1)}}, // S & W
			{'F', {std::make_pair(1, 0), std::make_pair(0, 1)}}, // S & E
		};

		const std::map<std::pair<int, int>, std::unordered_set<char>> NEIGHBOUR_MATCH{
			{std::make_pair(-1, 0), {'7', 'F', '|'}},
			{std::make_pair(1, 0), {'J', 'L', '|'}},
			{std::make_pair(0, -1), {'L', 'F', '-'}},
			{std::make_pair(0, 1), {'J', '7', '-'}},
		};

		// lambda for bounds checking
		auto in_bounds = [&MAX_ROW, &MAX_COL](const int& r, const int& c) -> bool {
			return r > -1 && r < MAX_ROW && c > -1 && c < MAX_COL;
			};

		graph::unweighted<T> u_graph;

		for (int r{}; r < MAX_ROW; ++r) {
			for (int c{}; c < MAX_COL; ++c) {
				if (g[r][c] == 'S' || g[r][c] == '.') {
					continue;
				}
				for (const auto& n : PIPE_NEIGHBOURS.at(g[r][c])) {
					int v{ r + n.first };
					int h{ c + n.second };

					if (!in_bounds(v, h)) {
						continue;
					}

					const std::unordered_set<char> MATCHES{ NEIGHBOUR_MATCH.at(n) };
					const char NEIGHBOUR{ g[v][h] };

					if (MATCHES.find(NEIGHBOUR) != MATCHES.end() || NEIGHBOUR == 'S') {
						graph::vertex<char> v1(c, r, g[r][c]);
						graph::vertex<char> v2(h, v, g[v][h]);
						u_graph.add_edge(v1, v2);
						u_graph.add_edge(v2, v1);
					}
				}

				
			}
		}

		return u_graph;
	}

	template<typename T = char>
	graph::result<T> find_cycle(const graph::unweighted<T>& graph, const graph::vertex<T>& start) {
		const auto GRAPH_DATA = graph.data();
		graph::result<T> r;
		r.path.reserve(graph.size()); // avoid reallocation for insertions
		std::stack<graph::vertex<T>> s;
		s.push(start);
		// Map is chosen to allow for easy backtracking.
		std::map<graph::vertex<T>, graph::vertex<T>> explored;
		explored[start] = start;
		graph::vertex<T> prev = start;
		while (!s.empty()) {
			graph::vertex<T> v = s.top();
			s.pop();
			++r.vertices_visited;
			for (const graph::vertex<T>& e : GRAPH_DATA.at(v)) {
				if (e == prev) {
					continue;
				}
				if (explored.find(e) == explored.end()) {
					explored[e] = v;
					s.push(e);
					continue;
				}
				if (explored[e] == start) {
					r.path.insert(r.path.begin(), e);
					r.path.insert(r.path.begin(), v);
					while (v != start) {
						v = explored[v];
						r.path.insert(r.path.begin(), v);
					}
					return r;
				}
			}
			prev = v;
		};
		// no result found - return empty path.
		return r;
	}

	template<typename T = char>
	grid<bool> mark_path_on_grid(const size_t& r, const size_t& c, const std::vector<graph::vertex<T>>& path) {
		grid<bool> grid(r, std::vector<bool>(c, false));

		for (const graph::vertex<T>& v : path) {
			grid[v.y][v.x] = true;
		}

		return grid;
	}

	template<typename T = char>
	size_t enclosed_area(const grid<bool>& path, const grid<char>& input) {
		size_t area{0};

		for (int i{ 0 }; i < path.size(); ++i) {
			bool enclosed{ false };
			for (int j{ 0 }; j < path.front().size(); ++j) {
				if (!path[i][j]) {
					if (enclosed) {
						//std::cout << "Enclosed at: " << i << ',' << j << '\n';
						++area;
					}
					continue;
				}
				if (input[i][j] == '-') {
					continue;
				}

				if (input[i][j] == '|' || input[i][j] == 'J' || input[i][j] == 'L') {
					enclosed = !enclosed;
					continue;
				}
			}
			
		}

		return area;
	}
}

