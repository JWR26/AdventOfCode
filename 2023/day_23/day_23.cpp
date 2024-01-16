#include "day_23.h"

void day_23::print_answers() {
	const std::string FILE{ aoc::get_test_file(2023, 23) };
	
	const std::vector<std::string> INPUT{ aoc::get_lines(FILE)};

	aoc::graph<char> graph{ build_graph(INPUT) };

	aoc::print_graph(graph);

	// optimise the graph

	std::cout << "Optimising graph...\n";

	aoc::optimise(graph);

	std::cout << "Optimised graph:\n";

	aoc::print_graph(graph);

	// topological sort

	// iterate topological order updating max distance
}

aoc::graph<char> day_23::build_graph(const std::vector<std::string>& input) {
	aoc::graph<char> graph;

	const int ROWS{ static_cast<int>(input.size()) };

	for (int r{}; r < ROWS; ++r) {
		const int COLUMNS{ static_cast<int>(input[r].size()) };
		for (int c{}; c < COLUMNS; ++c) {
			// '#' are walls
			if (input[r][c] == '#') {
				continue;
			}
			aoc::node<char> n(r * COLUMNS + c, input[r][c]);

			// look up
			if (r > 0) {
				if (input[r - 1][c] != '#') {
					aoc::node<char> up((r - 1) * COLUMNS + c, input[r - 1][c]);
					if (n.value == 'v' || up.value == 'v') {
						// can only move onto slope
						aoc::add_edge(graph, up, n);
					}
					else {
						aoc::add_edge(graph, n, up);
						aoc::add_edge(graph, up, n);
					}
				}
			}
			// look left
			if (c > 0) {
				if (input[r][c - 1] != '#') {
					aoc::node<char> left(r * COLUMNS + c - 1, input[r][c - 1]);
					if (n.value == '>' || left.value == '>') {
						// can only move onto slope
						aoc::add_edge(graph, left, n);
					}
					else {
						aoc::add_edge(graph, n, left);
						aoc::add_edge(graph, left, n);
					}
				}
			}
		}

	}

	return graph;
}