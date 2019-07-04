#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\PrintDataTable\Util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(fib)
		{
			Assert::AreEqual(2, Util::fib(3));
			Assert::AreEqual(5, Util::fib(5));
			Assert::AreEqual(6765, Util::fib(20));
		}

		TEST_METHOD(isFibonacci)
		{
			Assert::IsTrue(Util::isFibonacci(3));
			Assert::IsFalse(Util::isFibonacci(6));
			Assert::IsTrue(Util::isFibonacci(Util::fib(10)));
		}

		TEST_METHOD(add_number)
		{
			unordered_map<int, int> data;
			data.emplace(1, 2);
			data.emplace(3, 1);

			Util::add_number(data, 1);
			auto it = data.find(1);
			Assert::IsTrue(it != data.end());
			Assert::AreEqual(3, it->second);

			Util::add_number(data, 4);
			it = data.find(4);
			Assert::IsTrue(it != data.end());
			Assert::AreEqual(1, it->second);
		}

		TEST_METHOD(convert_data)
		{
			unordered_map<int, int> data;
			data.emplace(10, 2);
			data.emplace(2, 3);
			data.emplace(1, 3);
			data.emplace(3, 2);

			auto new_data = Util::convert_data(data);
			Assert::AreEqual((size_t)2, new_data.size());

			size_t n = 0;
			for (auto it = new_data.begin(); it != new_data.end(); it++, n++)
			{
				if (n == 0)
				{
					Assert::AreEqual(3, it->first);

					auto s = it->second;
					Assert::AreEqual((size_t)2, s.size());

					set<int> expected = { 1, 2 };
					Assert::IsTrue(expected == s);
				}
				else if (n == 1)
				{
					Assert::AreEqual(2, it->first);
					
					auto s = it->second;
					Assert::AreEqual((size_t)2, s.size());

					set<int> expected = { 3, 10 };
					Assert::IsTrue(expected == s);
				}
			}
		}
	};
}