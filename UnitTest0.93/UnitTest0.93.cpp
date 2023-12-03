#include "pch.h"
#include "CppUnitTest.h"
#include "../PR-09.3/PR-09.3.cpp"
#include "../PR-09.3/PR-09.3.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest093
{
    TEST_CLASS(UnitTest093)
    {
    public:

      
        TEST_METHOD(Metod1)
        {
            
			Client* p = new Client[3];
            string prizv, inits;
            cout << "Введіть прізвище клієнта:  " << endl;
            cin >> prizv;
            int N = 3;
			Assert::AreEqual(LineSearch(p, N);
			Assert::AreEqual(LineSearch(p, N);
        }
    };
}
