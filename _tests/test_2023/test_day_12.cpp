#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <vector>

#include "day_12/day_12.h"
#include "file_parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test2023
{
	TEST_CLASS(test_day12)
	{
	public:

		const std::string TEST_FILE{ "C:\\Users\\jonat\\source\\repos\\AdventOfCode\\2023\\day_12\\test.txt" };
		TEST_METHOD(TestSplitRecord)
		{
			const std::string INPUT{"???.### 1,1,3"};

			auto [SPRINGS, PATTERN] = day_12::split_record(INPUT);
			const std::string EXPECTED_SPRINGS{ "???.###" };

			Assert::AreEqual(EXPECTED_SPRINGS, SPRINGS);

			const std::vector<int> EXPECTED_PATTERN{ 1, 1, 3 };

			Assert::IsTrue(EXPECTED_PATTERN == PATTERN);
		}

		TEST_METHOD(TestSinglePossible)
		{
			const std::string INPUT{ "???.### 1,1,3" };

			auto [SPRINGS, PATTERN] = day_12::split_record(INPUT);

			const int ACTUAL = day_12::possible_arrangements(SPRINGS.begin(), SPRINGS.end(), PATTERN, 0, 0);

			const int EXPECTED{ 1 };

			Assert::AreEqual(EXPECTED, ACTUAL);
		}

		TEST_METHOD(TestMultiplePossible)
		{
			const std::string INPUT{ ".??..??...?##. 1,1,3" };

			auto [SPRINGS, PATTERN] = day_12::split_record(INPUT);

			const int ACTUAL = day_12::possible_arrangements(SPRINGS.begin(), SPRINGS.end(), PATTERN, 0, 0);

			const int EXPECTED{ 4 };

			Assert::AreEqual(EXPECTED, ACTUAL);
		}

		TEST_METHOD(TestManyPossible)
		{
			const std::string INPUT{ "?###???????? 3,2,1" };

			auto [SPRINGS, PATTERN] = day_12::split_record(INPUT);

			const int ACTUAL = day_12::possible_arrangements(SPRINGS.begin(), SPRINGS.end(), PATTERN, 0, 0);

			const int EXPECTED{ 10 };

			Assert::AreEqual(EXPECTED, ACTUAL);
		}

		TEST_METHOD(TestSumRecords)
		{
			const std::vector<std::string> INPUT{ file_parser::get_lines(TEST_FILE) };

			day_12::ConditionRecords records{ day_12::get_records(INPUT) };

			int actual{ day_12::sum_records(records) };

			int expected{ 21 };

			Assert::AreEqual(expected, actual);
		}
	};
}
