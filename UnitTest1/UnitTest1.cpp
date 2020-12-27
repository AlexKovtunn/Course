#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/transformationtopostfix.h"
#include "../ConsoleApplication1/strl.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TermWorkUnitTest
{
	TEST_CLASS(TermWorkUnitTest)
	{
	public:
		strl infix;

		TEST_METHOD(СorrectTest1)
		{
			infix = ") 2 + 2";
			fstream f;
			Assert::IsFalse(infix.checkinfix(f));
		}

		TEST_METHOD(СorrectTest2)
		{
			infix = "2+2";
			fstream f;
			Assert::IsFalse(infix.checkinfix(f));
		}

		TEST_METHOD(СorrectTest3)
		{
			infix = "( ( 2 + 2 ) * 2 ) / 8";
			fstream f;
			Assert::IsTrue(infix.checkinfix(f));
		}

		TEST_METHOD(ConversionTest1)
		{
			infix = "( ( 2 + 2 ) * 2 ) / 8";
			expression pf(infix);
			Assert::IsTrue(pf.getOutstr().isEqual("2 2 + 2 * 8 / "));
		}

		TEST_METHOD(ConversionTest2)
		{
			infix = "cos ( pi * 2 - ( 2 * pi ) )";
			expression pf(infix);
			Assert::IsTrue(pf.getOutstr().isEqual("pi 2 * 2 pi * - cos "));
		}

		TEST_METHOD(ConversionTest3)
		{
			infix = "10 + 3 * 5 / ( 16 - 4 )";
			expression pf(infix);
			Assert::IsTrue(pf.getOutstr().isEqual("10 3 5 * 16 4 - / + "));
		}

		TEST_METHOD(ConversionTest4)
		{
			infix = "5 * 3 ^ ( 4 - 2 )";
			expression pf(infix);
			Assert::IsTrue(pf.getOutstr().isEqual("5 3 4 2 - ^ * "));
		}

		TEST_METHOD(ConversionTest5)
		{
			infix = "( 2 + ( 3 + ( 4 + ( 5 + 6 * ( 7 + 8 ) ) ) ) )";
			expression pf(infix);
			Assert::IsTrue(pf.getOutstr().isEqual("2 3 4 5 6 7 8 + * + + + + "));
		}

		TEST_METHOD(CalculateTest1)
		{
			infix = "( 2 + ( 3 + ( 4 + ( 5 + 6 * ( 7 + 8 ) ) ) ) )";
			expression pf(infix);
			Assert::IsTrue(pf.calculate().isEqual(104));
		}

		TEST_METHOD(CalculateTest2)
		{
			infix = "cos ( pi * 2 - ( 2 * pi ) )";
			expression pf(infix);
			Assert::IsTrue(pf.calculate().isEqual(1));
		}

		TEST_METHOD(CalculateTest3)
		{
			infix = "( 2 + 3 * ( 4 ^ cos ( pi / 4 ) ) )";
			expression pf(infix);
			Assert::IsTrue(pf.calculate().isEqual(9.995435));
		}

		TEST_METHOD(CalculateTest4)
		{
			infix = "ln e";
			expression pf(infix);
			Assert::IsTrue(pf.calculate().isEqual(1));
		}

		TEST_METHOD(CalculateTest5)
		{
			infix = "51231.3213 * 12361.12";
			expression pf(infix);
			Assert::IsTrue(pf.calculate().isEqual(633276510.347856));
		}

	};
}
