#include "HeaderTask03.h"

bool ValidateInput(int InBase, int InDigitCount, std::string& OutErrorMessage)
{
    // Проверка основания системы счисления (2 ≤ K ≤ 10)
    if (InBase < 2 || InBase > 10)
    {
        OutErrorMessage = "Ошибка: Основание системы счисления K должно быть от 2 до 10. Получено: " +
            std::to_string(InBase);
        return false;
    }

    // Проверка количества разрядов (1 < N < 20)
    if (InDigitCount <= 1 || InDigitCount >= 20)
    {
        OutErrorMessage = "Ошибка: Количество разрядов N должно быть 1 < N < 20. Получено: " +
            std::to_string(InDigitCount);
        return false;
    }

    // Проверка условия N + K < 26
    if (InDigitCount + InBase >= 26)
    {
        OutErrorMessage = "Ошибка: Не выполнено условие N + K < 26. Текущее значение: " +
            std::to_string(InDigitCount + InBase);
        return false;
    }

    return true;
}

double CountValidNumbers(int InBase, int InDigitCount)
{
    //FIX_ME: некорректные имена переменных 
    //int i, k, n, nz, _nz, oz, _oz, tz, _tz, thz, _thz, fz, _fz;
    int DigitIndex;
    int Base;
    int DigitCount;

    int NonZeroCount, TempNonZeroCount;
    int OneZeroCount, TempOneZeroCount;
    int TwoZerosCount, TempTwoZerosCount;
    int ThreeZerosCount, TempThreeZerosCount;
    int FourOrMoreZerosCount, TempFourOrMoreZerosCount;

    Base = InBase;
    DigitCount = InDigitCount;

    //FIX_ME: улучшение читаемости переменных 
    //NonZeroCount=Base-1;
    //OneZeroCount=0;
    //TwoZerosCount=0;
    //ThreeZerosCount=0;
    //FourOrMoreZerosCount=0;
    NonZeroCount = Base - 1;
    OneZeroCount = 0;
    TwoZerosCount = 0;
    ThreeZerosCount = 0;
    FourOrMoreZerosCount = 0;

    for (DigitIndex = 2; DigitIndex <= DigitCount; DigitIndex++)
    {
        //FIX_ME: улучшение читаемости переменных 
        //TempNonZeroCount=NonZeroCount;
        //TempOneZeroCount=OneZeroCount;
        //TempTwoZerosCount=TwoZerosCount;
        //TempThreeZerosCount=ThreeZerosCount;
        //TempFourOrMoreZerosCount=FourOrMoreZerosCount;

        //NonZeroCount=TempNonZeroCount*(Base-1)+TempOneZeroCount*(Base-1)+TempTwoZerosCount*(Base-1)+TempThreeZerosCount*(Base-1
        //OneZeroCount=TempNonZeroCount;
        //TwoZerosCount=TempOneZeroCount;
        //ThreeZerosCount=TempTwoZerosCount;
        //if (DigitIndex < 6)
        //	FourOrMoreZerosCount=TempThreeZerosCount + TempFourOrMoreZerosCount*(Base-1);
        //else
        //	FourOrMoreZerosCount=TempThreeZerosCount + TempFourOrMoreZerosCount*Base;

        TempNonZeroCount = NonZeroCount;
        TempOneZeroCount = OneZeroCount;
        TempTwoZerosCount = TwoZerosCount;
        TempThreeZerosCount = ThreeZerosCount;
        TempFourOrMoreZerosCount = FourOrMoreZerosCount;

        NonZeroCount = TempNonZeroCount * (Base - 1) +
            TempOneZeroCount * (Base - 1) +
            TempTwoZerosCount * (Base - 1) +
            TempThreeZerosCount * (Base - 1);

        OneZeroCount = TempNonZeroCount;
        TwoZerosCount = TempOneZeroCount;
        ThreeZerosCount = TempTwoZerosCount;

        //FIX_ME: использование констант вместо неизвестных чисел
        //if (DigitIndex < 6)
        const int SpecialRuleThreshold = 6;

        if (DigitIndex < SpecialRuleThreshold)
        {
            FourOrMoreZerosCount = TempThreeZerosCount +
                TempFourOrMoreZerosCount * (Base - 1);
        }
        else
        {
            FourOrMoreZerosCount = TempThreeZerosCount +
                TempFourOrMoreZerosCount * Base;
        }
    }

    // Общее количество допустимых чисел - сумма всех, кроме запрещённых
    double Result = static_cast<double>(NonZeroCount) +
        static_cast<double>(OneZeroCount) +
        static_cast<double>(TwoZerosCount) +
        static_cast<double>(ThreeZerosCount);

    return Result;
}
