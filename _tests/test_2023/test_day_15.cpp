#include "pch.h"
#include "CppUnitTest.h"

#include <list>
#include <map>
#include <string>
#include <vector>

#include "day_15/day_15.h"
#include "day_15/day_15.cpp"

#include "file_parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test2023
{
	TEST_CLASS(test_day15)
	{
	public:
		const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_15\\test.txt" };

		TEST_METHOD(TestHashChar)
		{
			const char INPUT{ 'H' };
			
			const int ACTUAL{ day_15::hash_char(INPUT, 0) };

			const int EXPECETD{ 200 };

			Assert::AreEqual(EXPECETD, ACTUAL);
		}

		TEST_METHOD(TestUpdateHash)
		{
			const char INPUT{ 'A' };

			const int ACTUAL{ day_15::hash_char(INPUT, 200) };

			const int EXPECETD{ 153 };

			Assert::AreEqual(EXPECETD, ACTUAL);
		}

		TEST_METHOD(TestHashString)
		{
			const std::string INPUT{ "HASH" };

			const int ACTUAL{ day_15::hash_string(INPUT) };

			const int EXPECETD{ 52 };

			Assert::AreEqual(EXPECETD, ACTUAL);
		}

		TEST_METHOD(TestHashSequence)
		{
			const std::vector<std::string> INPUT{ file_parser::split_file_by(TEST_FILE, ',')};

			const int ACTUAL{ day_15::sum_sequence(INPUT) };

			const int EXPECETD{ 1320 };

			Assert::AreEqual(EXPECETD, ACTUAL);
		}

		TEST_METHOD(TestFillBoxes)
		{
			const std::vector<std::string> INPUT{ file_parser::split_file_by(TEST_FILE, ',') };

			std::map<int, std::list<day_15::lens>> actual{ day_15::fill_boxes(INPUT) };

			std::map<int, std::list<day_15::lens>> expected{
				{0, {day_15::lens("rn", 1), day_15::lens("cm", 2)}},
				{1, {}},
				{3, {day_15::lens("ot", 7), day_15::lens("ab", 5), day_15::lens("pc", 6)}},
			};

			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestFocalPower)
		{
			const std::vector<std::string> INPUT{ file_parser::split_file_by(TEST_FILE, ',') };

			std::map<int, std::list<day_15::lens>> boxes{ day_15::fill_boxes(INPUT) };

			int actual{ day_15::calculate_focal_power(boxes) };
			int expected{ 145 };

			Assert::AreEqual(expected, actual);
		}
	};
}
