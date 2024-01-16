#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <vector>

#include "day_11/day_11.h"
#include "file_parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test2023
{
	TEST_CLASS(test_day11)
	{
	public:

		const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_11\\test.txt" };

		TEST_METHOD(TestFindGalaxies)
		{
			const day_11::grid TEST_INPUT{ aoc::file_to_grid(TEST_FILE) };

			const std::vector<std::pair<int64_t, int64_t>> ACTUAL{ day_11::find_galaxies(TEST_INPUT) };


			const std::vector<std::pair<int64_t, int64_t>> EXPECTED{
				std::make_pair(0, 3),
				std::make_pair(1, 7),
				std::make_pair(2, 0),
				std::make_pair(4, 6),
				std::make_pair(5, 1),
				std::make_pair(6, 9),
				std::make_pair(8, 7),
				std::make_pair(9, 0),
				std::make_pair(9, 4),
			};

			Assert::IsTrue(EXPECTED == ACTUAL);
		}

		TEST_METHOD(TestFindEmptyRows)
		{
			const day_11::grid TEST_INPUT{ aoc::file_to_grid(TEST_FILE) };

			const std::vector<int64_t> ACTUAL{ day_11::find_empty_rows(TEST_INPUT) };

			const std::vector<int64_t> EXPECTED{ 3, 7 };

			Assert::IsTrue(EXPECTED == ACTUAL);
		}

		TEST_METHOD(TestFindEmptyColumns)
		{
			const day_11::grid TEST_INPUT{ aoc::file_to_grid(TEST_FILE) };

			const std::vector<int64_t> ACTUAL{ day_11::find_empty_columns(TEST_INPUT) };

			const std::vector<int64_t> EXPECTED{ 2, 5, 8 };

			Assert::IsTrue(EXPECTED == ACTUAL);
		}

		TEST_METHOD(TestAdjustedDifferences)
		{
			const std::vector<int64_t> VALUES{ 5, 7, 8 };
			
			int64_t a{ 2 };
			int64_t b{ 4 };

			int64_t expected{ 2 };
			int64_t actual{ day_11::calculate_adjusted_difference(a, b, VALUES) };
			Assert::AreEqual(expected, actual);

			// number order independant
			actual = day_11::calculate_adjusted_difference(b, a, VALUES);
			Assert::AreEqual(expected, actual);

			// in range
			b = 6;
			expected = 5;
			actual = day_11::calculate_adjusted_difference(b, a, VALUES);
			Assert::AreEqual(expected, actual);

			// all range
			b = 10;
			expected = 11;
			actual = day_11::calculate_adjusted_difference(b, a, VALUES);
			Assert::AreEqual(expected, actual);

		}

		TEST_METHOD(TestAdjustedManhattan)
		{
			const day_11::grid TEST_INPUT{ aoc::file_to_grid(TEST_FILE) };

			const std::vector<int64_t> ROWS{ day_11::find_empty_rows(TEST_INPUT) };


			const std::vector<int64_t> COLUMNS{ day_11::find_empty_columns(TEST_INPUT) };


			const std::pair<int64_t, int64_t> A{ std::make_pair(5, 1) };
			const std::pair<int64_t, int64_t> B{ std::make_pair(9, 4) };

			const int64_t ACTUAL{ day_11::calculate_adjusted_manhattan(A, B, ROWS, COLUMNS) };

			const int64_t EXPECTED{ 9 };

			Assert::AreEqual(EXPECTED, ACTUAL);
		}

		TEST_METHOD(TestPartOne)
		{
			const day_11::grid TEST_INPUT{ aoc::file_to_grid(TEST_FILE) };
			const std::vector<std::pair<int64_t, int64_t>> GALAXIES{ day_11::find_galaxies(TEST_INPUT) };
			const std::vector<int64_t> ROWS{ day_11::find_empty_rows(TEST_INPUT) };
			const std::vector<int64_t> COLUMNS{ day_11::find_empty_columns(TEST_INPUT) };

			const int64_t ACTUAL{ day_11::sum_shortest_paths(GALAXIES, ROWS, COLUMNS) };
			const int64_t EXPECTED{ 374 };
			Assert::AreEqual(EXPECTED, ACTUAL);
		}

		TEST_METHOD(TestPartTwoTen)
		{
			const day_11::grid TEST_INPUT{ aoc::file_to_grid(TEST_FILE) };
			const std::vector<std::pair<int64_t, int64_t>> GALAXIES{ day_11::find_galaxies(TEST_INPUT) };
			const std::vector<int64_t> ROWS{ day_11::find_empty_rows(TEST_INPUT) };
			const std::vector<int64_t> COLUMNS{ day_11::find_empty_columns(TEST_INPUT) };

			const int64_t FACTOR{ 9 };

			const int64_t ACTUAL{ day_11::sum_shortest_paths(GALAXIES, ROWS, COLUMNS, FACTOR) };
			const int64_t EXPECTED{ 1030 };
			Assert::AreEqual(EXPECTED, ACTUAL);
		}

		TEST_METHOD(TestPartTwoHundred)
		{
			const day_11::grid TEST_INPUT{ aoc::file_to_grid(TEST_FILE) };
			const std::vector<std::pair<int64_t, int64_t>> GALAXIES{ day_11::find_galaxies(TEST_INPUT) };
			const std::vector<int64_t> ROWS{ day_11::find_empty_rows(TEST_INPUT) };
			const std::vector<int64_t> COLUMNS{ day_11::find_empty_columns(TEST_INPUT) };

			const int64_t FACTOR{ 99 };

			const int64_t ACTUAL{ day_11::sum_shortest_paths(GALAXIES, ROWS, COLUMNS, FACTOR) };
			const int64_t EXPECTED{ 8410 };
			Assert::AreEqual(EXPECTED, ACTUAL);
		}
	};
}
