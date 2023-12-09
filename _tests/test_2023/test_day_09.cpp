#include "pch.h"
#include "CppUnitTest.h"

#include <vector>

#include "day_09/day_09.h"
#include "day_09/day_09.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test2023
{
	TEST_CLASS(test_day09)
	{
	public:

		TEST_METHOD(TestPredictNext)
		{
			std::vector<int> input{ 0, 3, 6, 9, 12, 15 };
			int actual{ day_09::predict_next(input, 0) };
			int expected{ 18 };
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestPredictNextDecreasing)
		{
			std::vector<int> input{ 0, -3, -6, -9, -12, -15 };
			int actual{ day_09::predict_next(input, 0) };
			int expected{ -18 };
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestSumPredictions)
		{
			std::vector<std::vector<int>> input{ 
				{0, 3, 6, 9, 12, 15}, 
				{1, 3, 6, 10, 15, 21},
				{10, 13, 16, 21, 30, 45},
			};
			long long actual{ day_09::sum_extrapolated_values(input) };
			long long expected{ 114 };
			Assert::AreEqual(expected, actual);
		}
	};
}
