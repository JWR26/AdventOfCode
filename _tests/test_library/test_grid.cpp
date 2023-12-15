#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <vector>

#include "grid.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testlibrary
{
	TEST_CLASS(TestGrid)
	{
	public:

		TEST_METHOD(TestRowIteration)
		{
			const std::vector<char> data{ 'a', 'a', 'a', 'b', 'b', 'b', 'c', 'c', 'c' };
			aoc::grid<char> g(data, 3, 3);

			aoc::grid<char>::row_iterator rit{ g.row_begin(1) };

			while (rit != g.row_end(1)) {

			}

		}
	};
}
