#include "pch.h"
#include "CppUnitTest.h"

#include <vector>

#include "day_10/day_10.h"
#include "day_10/day_10.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test2023
{
	TEST_CLASS(test_day10)
	{
	public:
		using grid = std::vector<std::vector<char>>;

		const std::string TEST_LOOP{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_10\\test_loop.txt" };
		const std::string TEST_SLOOP{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_10\\test_sloop.txt" };
		const std::string TEST_A{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_10\\testa.txt" };
		const std::string TEST_B{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_10\\testb.txt" };
		const std::string TEST_C{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_10\\testc.txt" };
		const std::string TEST_D{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_10\\testd.txt" };
		const std::string TEST_E{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_10\\teste.txt" };

		TEST_METHOD(TestBuildGraphSimple)
		{
			graph::unweighted<char> expected;
			expected.add_edge(graph::vertex<char>(1, 1, 'F'), graph::vertex<char>(2, 1, '-'));
			expected.add_edge(graph::vertex<char>(2, 1, '-'), graph::vertex<char>(1, 1, 'F'));
			expected.add_edge(graph::vertex<char>(3, 1, '7'), graph::vertex<char>(2, 1, '-'));
			expected.add_edge(graph::vertex<char>(2, 1, '-'), graph::vertex<char>(3, 1, '7'));
			expected.add_edge(graph::vertex<char>(1, 1, 'F'), graph::vertex<char>(1, 2, '|'));
			expected.add_edge(graph::vertex<char>(1, 2, '|'), graph::vertex<char>(1, 1, 'F'));
			expected.add_edge(graph::vertex<char>(3, 1, '7'), graph::vertex<char>(3, 2, '|'));
			expected.add_edge(graph::vertex<char>(3, 2, '|'), graph::vertex<char>(3, 1, '7'));
			expected.add_edge(graph::vertex<char>(1, 3, 'L'), graph::vertex<char>(1, 2, '|'));
			expected.add_edge(graph::vertex<char>(1, 2, '|'), graph::vertex<char>(1, 3, 'L'));
			expected.add_edge(graph::vertex<char>(3, 3, 'J'), graph::vertex<char>(3, 2, '|'));
			expected.add_edge(graph::vertex<char>(3, 2, '|'), graph::vertex<char>(3, 3, 'J'));
			expected.add_edge(graph::vertex<char>(1, 3, 'L'), graph::vertex<char>(2, 3, '-'));
			expected.add_edge(graph::vertex<char>(2, 3, '-'), graph::vertex<char>(1, 3, 'L'));
			expected.add_edge(graph::vertex<char>(3, 3, 'J'), graph::vertex<char>(2, 3, '-'));
			expected.add_edge(graph::vertex<char>(2, 3, '-'), graph::vertex<char>(3, 3, 'J'));

			grid test_input{ aoc::file_to_grid(TEST_LOOP) };
			graph::unweighted<char> actual{ day_10::build_graph<char>(test_input) };
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestBuildGraphWithStart)
		{
			graph::unweighted<char> expected;
			expected.add_edge(graph::vertex<char>(1, 1, 'S'), graph::vertex<char>(2, 1, '-'));
			expected.add_edge(graph::vertex<char>(2, 1, '-'), graph::vertex<char>(1, 1, 'S'));
			expected.add_edge(graph::vertex<char>(3, 1, '7'), graph::vertex<char>(2, 1, '-'));
			expected.add_edge(graph::vertex<char>(2, 1, '-'), graph::vertex<char>(3, 1, '7'));
			expected.add_edge(graph::vertex<char>(1, 1, 'S'), graph::vertex<char>(1, 2, '|'));
			expected.add_edge(graph::vertex<char>(1, 2, '|'), graph::vertex<char>(1, 1, 'S'));
			expected.add_edge(graph::vertex<char>(3, 1, '7'), graph::vertex<char>(3, 2, '|'));
			expected.add_edge(graph::vertex<char>(3, 2, '|'), graph::vertex<char>(3, 1, '7'));
			expected.add_edge(graph::vertex<char>(1, 3, 'L'), graph::vertex<char>(1, 2, '|'));
			expected.add_edge(graph::vertex<char>(1, 2, '|'), graph::vertex<char>(1, 3, 'L'));
			expected.add_edge(graph::vertex<char>(3, 3, 'J'), graph::vertex<char>(3, 2, '|'));
			expected.add_edge(graph::vertex<char>(3, 2, '|'), graph::vertex<char>(3, 3, 'J'));
			expected.add_edge(graph::vertex<char>(1, 3, 'L'), graph::vertex<char>(2, 3, '-'));
			expected.add_edge(graph::vertex<char>(2, 3, '-'), graph::vertex<char>(1, 3, 'L'));
			expected.add_edge(graph::vertex<char>(3, 3, 'J'), graph::vertex<char>(2, 3, '-'));
			expected.add_edge(graph::vertex<char>(2, 3, '-'), graph::vertex<char>(3, 3, 'J'));

			grid test_input{ aoc::file_to_grid(TEST_SLOOP) };
			graph::unweighted<char> actual{ day_10::build_graph<char>(test_input) };
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestBuildFull)
		{
			graph::unweighted<char> expected;
			// represent the loop
			expected.add_edge(graph::vertex<char>(1, 1, 'S'), graph::vertex<char>(2, 1, '-'));
			expected.add_edge(graph::vertex<char>(2, 1, '-'), graph::vertex<char>(1, 1, 'S'));
			expected.add_edge(graph::vertex<char>(3, 1, '7'), graph::vertex<char>(2, 1, '-'));
			expected.add_edge(graph::vertex<char>(2, 1, '-'), graph::vertex<char>(3, 1, '7'));
			expected.add_edge(graph::vertex<char>(1, 1, 'S'), graph::vertex<char>(1, 2, '|'));
			expected.add_edge(graph::vertex<char>(1, 2, '|'), graph::vertex<char>(1, 1, 'S'));
			expected.add_edge(graph::vertex<char>(3, 1, '7'), graph::vertex<char>(3, 2, '|'));
			expected.add_edge(graph::vertex<char>(3, 2, '|'), graph::vertex<char>(3, 1, '7'));
			expected.add_edge(graph::vertex<char>(1, 3, 'L'), graph::vertex<char>(1, 2, '|'));
			expected.add_edge(graph::vertex<char>(1, 2, '|'), graph::vertex<char>(1, 3, 'L'));
			expected.add_edge(graph::vertex<char>(3, 3, 'J'), graph::vertex<char>(3, 2, '|'));
			expected.add_edge(graph::vertex<char>(3, 2, '|'), graph::vertex<char>(3, 3, 'J'));
			expected.add_edge(graph::vertex<char>(1, 3, 'L'), graph::vertex<char>(2, 3, '-'));
			expected.add_edge(graph::vertex<char>(2, 3, '-'), graph::vertex<char>(1, 3, 'L'));
			expected.add_edge(graph::vertex<char>(3, 3, 'J'), graph::vertex<char>(2, 3, '-'));
			expected.add_edge(graph::vertex<char>(2, 3, '-'), graph::vertex<char>(3, 3, 'J'));
			// pipes not in loop
			expected.add_edge(graph::vertex<char>(0, 1, '7'), graph::vertex<char>(0, 2, 'L'));
			expected.add_edge(graph::vertex<char>(0, 2, 'L'), graph::vertex<char>(0, 1, '7'));
			expected.add_edge(graph::vertex<char>(3, 0, 'F'), graph::vertex<char>(4, 0, '7'));
			expected.add_edge(graph::vertex<char>(4, 0, '7'), graph::vertex<char>(3, 0, 'F'));
			expected.add_edge(graph::vertex<char>(4, 1, '|'), graph::vertex<char>(4, 0, '7'));
			expected.add_edge(graph::vertex<char>(4, 0, '7'), graph::vertex<char>(4, 1, '|'));
			expected.add_edge(graph::vertex<char>(4, 1, '|'), graph::vertex<char>(4, 2, '|'));
			expected.add_edge(graph::vertex<char>(4, 2, '|'), graph::vertex<char>(4, 1, '|'));
			expected.add_edge(graph::vertex<char>(4, 3, '|'), graph::vertex<char>(4, 2, '|'));
			expected.add_edge(graph::vertex<char>(4, 2, '|'), graph::vertex<char>(4, 3, '|'));
			expected.add_edge(graph::vertex<char>(3, 4, 'J'), graph::vertex<char>(2, 4, '-'));
			expected.add_edge(graph::vertex<char>(2, 4, '-'), graph::vertex<char>(3, 4, 'J'));

			grid test_input{ aoc::file_to_grid(TEST_A) };
			graph::unweighted<char> actual{ day_10::build_graph<char>(test_input) };
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestFindSimpleCycle) 
		{
			grid test_input{ aoc::file_to_grid(TEST_SLOOP) };
			graph::unweighted<char> graph{ day_10::build_graph<char>(test_input) };
			graph::vertex<char> start{ graph.find_vertex('S') };

			graph::result<char> cycle{ day_10::find_cycle(graph, start) };

			size_t actual{ cycle.path.size() };
			size_t expected{ 8 };

			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestMarkPathGrid)
		{
			grid test_input{ aoc::file_to_grid(TEST_SLOOP) };
			graph::unweighted<char> graph{ day_10::build_graph<char>(test_input) };
			graph::vertex<char> start{ graph.find_vertex('S') };
			graph::result<char> cycle{ day_10::find_cycle(graph, start) };

			std::vector<std::vector<bool>> actual{ day_10::mark_path_on_grid(test_input.size(), test_input.front().size(), cycle.path) };

			std::vector<std::vector<bool>> expected{
				{false, false, false, false, false},
				{false, true, true, true, false},
				{false, true, false, true, false},
				{false, true, true, true, false},
				{false, false, false, false, false},
			};

			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestEnclosedArea) 
		{
			grid test_input{ aoc::file_to_grid(TEST_C) };
			graph::unweighted<char> graph{ day_10::build_graph<char>(test_input) };
			graph::vertex<char> start{ graph.find_vertex('S') };
			graph::result<char> cycle{ day_10::find_cycle(graph, start) };
			std::vector<std::vector<bool>> marked_path{ day_10::mark_path_on_grid(test_input.size(), test_input.front().size(), cycle.path) };

			size_t actual{ day_10::enclosed_area(marked_path, test_input) };
			size_t expected{ 4 };

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestLargerArea)
		{
			grid test_input{ aoc::file_to_grid(TEST_D) };
			graph::unweighted<char> graph{ day_10::build_graph<char>(test_input) };
			graph::vertex<char> start{ graph.find_vertex('S') };
			graph::result<char> cycle{ day_10::find_cycle(graph, start) };
			std::vector<std::vector<bool>> marked_path{ day_10::mark_path_on_grid(test_input.size(), test_input.front().size(), cycle.path) };

			size_t actual{ day_10::enclosed_area(marked_path, test_input) };
			size_t expected{ 8 };

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestComplexArea)
		{
			grid test_input{ aoc::file_to_grid(TEST_E) };
			graph::unweighted<char> graph{ day_10::build_graph<char>(test_input) };
			graph::vertex<char> start{ graph.find_vertex('S') };
			graph::result<char> cycle{ day_10::find_cycle(graph, start) };
			std::vector<std::vector<bool>> marked_path{ day_10::mark_path_on_grid(test_input.size(), test_input.front().size(), cycle.path) };

			size_t actual{ day_10::enclosed_area(marked_path, test_input) };
			size_t expected{ 10 };

			Assert::AreEqual(expected, actual);
		}
	};
}
