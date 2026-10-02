#include "HeaderTask02.h"

bool ContainsInvalidChars(const std::string& InLine)
{
    for (char Character : InLine)
    {
        const bool bIsValid = isdigit(static_cast<unsigned char>(Character)) ||
            isspace(static_cast<unsigned char>(Character)) ||
            Character == '-';

        if (!bIsValid)
        {
            return true; // Найден недопустимый символ
        }
    }
    return false; // Все символы допустимы
}
