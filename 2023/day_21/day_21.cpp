#include "day_21.h"

void day_21::print_answers() {
	std::cout << DAY_NAME;

	const std::vector<std::vector<char>> INPUT{ aoc::file_to_grid(INPUT_FILE) };

	const auto [GRAPH, START] { grid_to_graph(INPUT) };

	const std::vector<int> DESTINATIONS{ reach_in_steps(GRAPH, START, 64) };

	std::cout << "Part 1: " << DESTINATIONS.size() << '\n';


}

std::pair<day_21::graph, int> day_21::grid_to_graph(const std::vector<std::vector<char>>& grid) {
	graph g;

	int start{ 0 };

	const int R{ static_cast<int>(grid.size()) };
	const int C{ static_cast<int>(grid.front().size()) };

	for (int i{}; i < R; ++i) {
		for (int j{}; j < C; ++j) {
			if (grid[i][j] == ROCK) {
				continue;
			}

			if (grid[i][j] == START) {
				start = i * C + j;
			}

			if (i > 0) {
				if (grid[i - 1][j] != ROCK) {
					g[i * C + j].push_back((i - 1) * C + j);
					g[(i - 1) * C + j].push_back(i * C + j);
				}
			}
			if (j > 0) {
				if (grid[i][j - 1] != ROCK) {
					g[i * C + j].push_back(i * C + j - 1);
					g[i * C + j - 1].push_back(i * C + j);
				}
			}
		}
	}

	return std::make_pair(g, start);
}

std::vector<int> day_21::reach_in_steps(const graph& g, const int& start, const int& steps) {
	std::vector<int> reached;
	std::unordered_set<int> visited;
	std::queue<std::pair<int, int>> q;

	const int POR{ steps % 2 };

	q.push(std::make_pair(start, 0));
	visited.insert(start);

	while (!q.empty()) {
		std::pair<int,int> front{ q.front() };
		const auto [CURRENT, STEPS] { front };
		q.pop();

		if (STEPS > steps) {
			continue;
		}

		if (STEPS % 2 == POR) {
			reached.push_back(CURRENT);
		}

		for (const int& NEIGHBOUR : g.at(CURRENT)) {
			if (visited.find(NEIGHBOUR) == visited.end()) {
				q.push(std::make_pair(NEIGHBOUR, STEPS + 1));
				visited.insert(NEIGHBOUR);
			}
		}
	}

	return reached;
}