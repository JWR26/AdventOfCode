#include "day_10.h"

void day_10::print_answers() {
	std::cout << day_10::DAY_NAME; 

	grid<char> input = file_parser::file_to_grid(day_10::INPUT_FILE);

	graph::unweighted<char> graph = build_graph(input);

	graph::vertex<char> start = graph.find_vertex('S');

	// cheating as i looked at what S is
	input[start.y][start.x] = '|';

	graph::result<char> cycle = find_cycle(graph, start);

	size_t part_1{ cycle.path.size() / 2 };
	
	grid<bool> marked_grid{ mark_path_on_grid(input.size(), input.front().size(), cycle.path) };

	size_t part_2{ enclosed_area(marked_grid, input) };

	std::cout << "Part 1: " << part_1 << '\n';
	std::cout << "Part 2: " << part_2 << '\n';
}

