#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <vector>

#include "day_12/day_12.h"
#include "day_12/day_12.cpp"
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

			const std::vector<size_t> EXPECTED_PATTERN{ 1, 1, 3 };

			Assert::IsTrue(EXPECTED_PATTERN == PATTERN);
		}

		TEST_METHOD(TestSinglePossible)
		{
			const std::string INPUT{ "???.### 1,1,3" };

			auto [SPRINGS, PATTERN] = day_12::split_record(INPUT);

			day_12::Cache cache;

			const size_t ACTUAL = day_12::possible_arrangements(SPRINGS.begin(), SPRINGS.end(), PATTERN, 0, 0, cache);

			const size_t EXPECTED{ 1 };

			Assert::AreEqual(EXPECTED, ACTUAL);
		}

		TEST_METHOD(TestMultiplePossible)
		{
			const std::string INPUT{ ".??..??...?##. 1,1,3" };

			auto [SPRINGS, PATTERN] = day_12::split_record(INPUT);

			day_12::Cache cache;

			const size_t ACTUAL = day_12::possible_arrangements(SPRINGS.begin(), SPRINGS.end(), PATTERN, 0, 0, cache);

			const size_t EXPECTED{ 4 };

			Assert::AreEqual(EXPECTED, ACTUAL);
		}

		TEST_METHOD(TestManyPossible)
		{
			const std::string INPUT{ "?###???????? 3,2,1" };

			auto [SPRINGS, PATTERN] = day_12::split_record(INPUT);

			day_12::Cache cache;

			const size_t ACTUAL = day_12::possible_arrangements(SPRINGS.begin(), SPRINGS.end(), PATTERN, 0, 0, cache);

			const size_t EXPECTED{ 10 };

			Assert::AreEqual(EXPECTED, ACTUAL);
		}

		TEST_METHOD(TestSumRecords)
		{
			const std::vector<std::string> INPUT{ file_parser::get_lines(TEST_FILE) };

			day_12::ConditionRecords records{ day_12::get_records(INPUT) };

			size_t actual{ day_12::sum_records(records) };

			size_t expected{ 21 };

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestSumRecordsPart1)
		{
			const std::vector<std::string> INPUT{ file_parser::get_lines(day_12::INPUT_FILE) };

			day_12::ConditionRecords records{ day_12::get_records(INPUT) };

			size_t actual{ day_12::sum_records(records) };

			size_t expected{ 6949 };

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestUnfoldRecord)
		{
			const std::string INPUT{ ".# 1" };

			day_12::Record actual{ day_12::split_record(INPUT) };

			day_12::unfold_record(actual);

			day_12::Record expected{ day_12::split_record(".#?.#?.#?.#?.# 1,1,1,1,1") };

			Assert::IsTrue(expected.first == actual.first);
			Assert::IsTrue(expected.second == actual.second);
		}

		TEST_METHOD(TestUnfoldedRecord)
		{
			const std::string INPUT{ "?###???????? 3,2,1" };

			day_12::Record rec = day_12::split_record(INPUT);

			day_12::unfold_record(rec);

			auto [SPRINGS, PATTERN] = rec;

			day_12::Cache cache;

			const size_t ACTUAL = day_12::possible_arrangements(SPRINGS.begin(), SPRINGS.end(), PATTERN, 0, 0, cache);

			const size_t EXPECTED{ 506250 };

			Assert::AreEqual(EXPECTED, ACTUAL);
		}

		TEST_METHOD(TestAllUnfolded)
		{
			const std::vector<std::string> INPUT{ file_parser::get_lines(TEST_FILE) };

			day_12::ConditionRecords records{ day_12::get_records(INPUT) };

			for (auto& rec : records) {
				day_12::unfold_record(rec);
			}
			
			size_t actual{ day_12::sum_records(records) };

			size_t expected{ 525152 };

			Assert::AreEqual(expected, actual);
		}
	};
}
