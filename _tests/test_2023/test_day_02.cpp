#include "pch.h"
#include "CppUnitTest.h"

#include <string>

#include "day_02/day_02.h"
#include "day_02/day_02.cpp"

#include "file_parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test2023
{
	TEST_CLASS(test_day02)
	{
	public:
		// test file for reference
		const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_02\\test.txt" };

		TEST_METHOD(TestStringToGameSimple)
		{
			day_02::Game expected(11, 3, 5, 4);
			std::string str{ "Game 11: 3 red, 5 green, 4 blue" };
			day_02::Game actual = day_02::to_game(str);
			Assert::AreEqual(expected.id, actual.id);
			Assert::AreEqual(expected.max_red, actual.max_red);
			Assert::AreEqual(expected.max_green, actual.max_green);
			Assert::AreEqual(expected.max_blue, actual.max_blue);
		}

		TEST_METHOD(TestStringToGameComplex)
		{
			day_02::Game expected(3, 20, 13, 6);
			std::string str{ "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red" };
			day_02::Game actual = day_02::to_game(str);
			Assert::AreEqual(expected.id, actual.id);
			Assert::AreEqual(expected.max_red, actual.max_red);
			Assert::AreEqual(expected.max_green, actual.max_green);
			Assert::AreEqual(expected.max_blue, actual.max_blue);
		}

		TEST_METHOD(TestPossibleGames)
		{
			day_02::Game game(0, 12, 13, 14);
			Assert::IsTrue(day_02::is_possible(game));
		}
		TEST_METHOD(TestRedNotPossible)
		{
			day_02::Game game_red(0, 13, 10, 10);
			Assert::IsFalse(day_02::is_possible(game_red));
		}
		TEST_METHOD(TestGreenNotPossible)
		{
			day_02::Game game_green(0, 10, 14, 10);
			Assert::IsFalse(day_02::is_possible(game_green));
		}

		TEST_METHOD(TestBlueNotPossible)
		{
			day_02::Game game_blue(0, 10, 10, 15);
			Assert::IsFalse(day_02::is_possible(game_blue));
		}

		TEST_METHOD(TestCubePower)
		{
			int expected{ 1560 };
			std::string str{ "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red" };
			day_02::Game game = day_02::to_game(str);
			int actual{ day_02::cube_power(game) };
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestParseTestFile)
		{
			std::vector<std::string> test_input{ file_parser::get_lines(TEST_FILE) };
			std::vector<day_02::Game> game_list{ day_02::to_game_list(test_input) };
			// validate list length
			size_t expected_size{ 5 };
			Assert::AreEqual(expected_size, game_list.size());
			//check first & last games (assume ones between are correct from String to game tests
			day_02::Game first(1, 4, 2, 6);
			day_02::Game actual(game_list.front());
			Assert::AreEqual(first.id, actual.id);
			Assert::AreEqual(first.max_red, actual.max_red);
			Assert::AreEqual(first.max_green, actual.max_green);
			Assert::AreEqual(first.max_blue, actual.max_blue);

			day_02::Game last(5, 6, 3, 2);
			day_02::Game actual_last(game_list.back());
			Assert::AreEqual(last.id, actual_last.id);
			Assert::AreEqual(last.max_red, actual_last.max_red);
			Assert::AreEqual(last.max_green, actual_last.max_green);
			Assert::AreEqual(last.max_blue, actual_last.max_blue);
		}

		TEST_METHOD(TestSumPossibleGameIds)
		{
			std::vector<std::string> test_input{ file_parser::get_lines(TEST_FILE) };
			std::vector<day_02::Game> game_list{ day_02::to_game_list(test_input) };
			int actual{ day_02::sum_possible_game_ids(game_list) };
			int expected{ 8 };
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestSumCubePowers)
		{
			std::vector<std::string> test_input{ file_parser::get_lines(TEST_FILE) };
			std::vector<day_02::Game> game_list{ day_02::to_game_list(test_input) };
			int actual{ day_02::sum_cube_powers(game_list) };
			int expected{ 2286 };
			Assert::AreEqual(expected, actual);
		}
	};
}
