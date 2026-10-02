#include "HeaderTask01.h"

//FIX_ME: В исходном коде глобально используется «using namespace std;», это загрязняет глобальное пространство имён. 
//Для всего кода заменено на префекс «std::».
//using namespace std;

//FIX_ME: Присутствует некорректное название функции «findAnswer». Данное название не соответствует стилю именования (PascalCase). 
//Функция переименована в «FindAnswer».
//void findAnswer(const std::vector<std::vector<int>>& dp, int k,int s, std::vector<int>& weight, std::vector<int>& nalog)
//{
//    if (k==0) {
//        return;
//    }
//    if (dp[k][s] == dp[k - 1][s]) {
//        findAnswer(dp, k - 1, s, weight,nalog);
//    }
//    else {
//        std::cout <<"выбрать предмет под номером " << k << ", ";
//        findAnswer(dp, k - 1, s - weight[k], weight,nalog);
//    }
//}
void FindAnswer(const std::vector<std::vector<int>>& OutDPTable,
    int CurrentIndex, int CurrentWeight, std::vector<int>& OutWeights, std::vector<int>& OutTaxes)
{
    if (CurrentIndex == 0) {
        return;
    }
    //FIX_ME: неправильное название переменной
    //if (InDPTable[CurrentIndex][CurrentWeight] == InDPTable[CurrentIndex - 1][CurrentWeight]) {
    //    FindAnswer(InDPTable, CurrentIndex - 1, CurrentWeight, InWeights, InTaxes);
    //}
    //else {
    //    std::cout << "выбрать предмет под номером " << CurrentIndex << ", ";
    //    FindAnswer(InDPTable, CurrentIndex - 1, CurrentWeight - InWeights[CurrentIndex], InWeights, InTaxes);
    //}
    if (OutDPTable[CurrentIndex][CurrentWeight] == OutDPTable[CurrentIndex - 1][CurrentWeight])
    {
        FindAnswer(OutDPTable, CurrentIndex - 1, CurrentWeight, OutWeights, OutTaxes);
    }
    else
    {
        std::cout << "выбрать предмет под номером " << CurrentIndex << ", ";
        FindAnswer(OutDPTable, CurrentIndex - 1, CurrentWeight - OutWeights[CurrentIndex], OutWeights, OutTaxes);
    }
}

bool ContainsInvalidChars(const std::string& InLine)
{
    for (char Character : InLine)
    {
        const bool bIsValid = isdigit(static_cast<unsigned char>(Character)) ||
            isspace(static_cast<unsigned char>(Character)) ||
            Character == '-' ||
            Character == '\n' ||
            Character == '\r';

        if (!bIsValid)
        {
            return true; // недопустимый символ
        }
    }

    return false; // все символы допустимы
}
