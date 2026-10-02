//К - ичные числа.Среди чисел в системе счисления с основанием K(2≤K≤10) определить сколько 
//имеется чисел из N(1 < N < 20, N + K < 26) разрядов таких, что в их записи не содержится 
//более трех подряд идущих нулей.Для того, чтобы избежать переполнения, ответ
//представьте в виде вещественного числа.

#ifndef HeaderTask03
#define HeaderTask03

#include <iostream>
#include <string>
#include <sstream>

//FIX_ME: использование глобального std;
//using namespace std;

bool ValidateInput(int InBase, int InDigitCount, std::string& OutErrorMessage);

double CountValidNumbers(int InBase, int InDigitCount);

#endif // HeaderTask03
