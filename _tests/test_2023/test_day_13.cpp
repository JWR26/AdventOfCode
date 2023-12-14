#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <vector>

#include "day_13/day_13.h"
#include "day_13/day_13.cpp"

#include "file_parser.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test2023
{
	TEST_CLASS(test_day13)
	{
	public:
		const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_13\\test.txt" };
		TEST_METHOD(TestFindMirrorLine)
		{
			const std::vector<std::string> INPUT{
				"#...##..#",
				"#....#..#",
				"..##..###",
				"#####.##.",
				"#####.##.",
				"..##..###",
				"#....#..#",
			};

			int actual{ day_13::find_reflection_line(INPUT.begin(), INPUT.end()) };
			int expected{ 4 };
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestNoMirrorLine)
		{
			const std::vector<std::string> INPUT{
				"#.##..##.",
				"..#.##.#.",
				"##......#",
				"##......#",
				"..#.##.#.",
				"..##..##.",
				"#.#.##.#.",
			};

			int actual{ day_13::find_reflection_line(INPUT.begin(), INPUT.end()) };
			int expected{ 0 };
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestTransposition)
		{
			const std::vector<std::string> INPUT{
				"abcde",
				"abcde",
				"abcde",
				"abcde",
				"abcde",
			};

			std::vector<std::string> actual{ day_13::transpose(INPUT) };
			std::vector<std::string> expected{
				"aaaaa",
				"bbbbb",
				"ccccc",
				"ddddd",
				"eeeee",
			};

			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestTransposedMirrorLine)
		{
			const std::vector<std::string> INPUT{
				"#.##..##.",
				"..#.##.#.",
				"##......#",
				"##......#",
				"..#.##.#.",
				"..##..##.",
				"#.#.##.#.",
			};

			std::vector<std::string> transposed{ day_13::transpose(INPUT) };

			int actual{ day_13::find_reflection_line(transposed.begin(), transposed.end()) };
			int expected{ 5 };
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestHorizontalScore)
		{
			const std::vector<std::string> INPUT{
				"#...##..#",
				"#....#..#",
				"..##..###",
				"#####.##.",
				"#####.##.",
				"..##..###",
				"#....#..#",
			};

			int actual{ day_13::reflection_line_score(INPUT) };
			int expected{ 400 };
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestVerticalScore)
		{
			const std::vector<std::string> INPUT{
				"#.##..##.",
				"..#.##.#.",
				"##......#",
				"##......#",
				"..#.##.#.",
				"..##..##.",
				"#.#.##.#.",
			};

			int actual{ day_13::reflection_line_score(INPUT) };
			int expected{ 5 };
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestPart1)
		{
			const std::vector<std::vector<std::string>> INPUT{ file_parser::get_paragraphs(TEST_FILE) };

			int actual{ day_13::summarise_notes(INPUT) };
			int expected{ 405 };

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestSingleMissmatch)
		{
			std::string a{ "..##..#" };
			std::string b{ "...#..#" };

			std::string::iterator actual{ day_13::single_mismatch(a, b) };
			std::string::iterator expected{ a.begin() + 2 };

			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestNoMissmatch)
		{
			std::string a{ "..##..#" };
			std::string b{ "..##..#" };

			std::string::iterator actual{ day_13::single_mismatch(a, b) };
			std::string::iterator expected{ a.end() };

			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestMultipleMissmatch)
		{
			std::string a{ "..##.##" };
			std::string b{ "...#..#" };

			std::string::iterator actual{ day_13::single_mismatch(a, b) };
			std::string::iterator expected{ a.end()};

			Assert::IsTrue(expected == actual);
		}
	};
}
