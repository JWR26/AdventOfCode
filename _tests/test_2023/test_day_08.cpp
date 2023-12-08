#include "pch.h"
#include "CppUnitTest.h"

#include <queue>
#include <string>

#include "day_08/day_08.h"
#include "day_08/day_08.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test2023
{
	TEST_CLASS(test_day08)
	{
	public:
		
		TEST_METHOD(TestGetInstructions)
		{
			const std::string input{ "RLRLRL" };
			const std::queue<char> ACTUAL{ day_08::get_instructions(input) };

			const std::queue<char> EXPECTED{ {'R', 'L','R', 'L', 'R', 'L'} };
			
			Assert::IsTrue(EXPECTED == ACTUAL);
		}
	};
}
