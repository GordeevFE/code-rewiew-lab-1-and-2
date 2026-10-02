#include "HeaderTask03.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    try
    {
        int Base;
        int DigitCount;

        // Ââîä îñíîâàíèÿ ñèñòåìû ñ÷èñëåíèÿ
        std::cout << "Ââåäèòå îñíîâàíèå ñèñòåìû ñ÷èñëåíèÿ K (2-10): ";
        if (!(std::cin >> Base))
        {
            throw std::runtime_error("Îøèáêà: Íå óäàëîñü ïðî÷èòàòü îñíîâàíèå ñèñòåìû ñ÷èñëåíèÿ");
        }

        // Ââîä êîëè÷åñòâà ðàçðÿäîâ
        std::cout << "Ââåäèòå êîëè÷åñòâî ðàçðÿäîâ N (1 < N < 20): ";
        if (!(std::cin >> DigitCount))
        {
            throw std::runtime_error("Îøèáêà: Íå óäàëîñü ïðî÷èòàòü êîëè÷åñòâî ðàçðÿäîâ");
        }

        // Ïðîâåðêà êîððåêòíîñòè âõîäíûõ äàííûõ
        std::string ErrorMessage;
        if (!ValidateInput(Base, DigitCount, ErrorMessage))
        {
            throw std::runtime_error(ErrorMessage);
        }

        // Âû÷èñëåíèå ðåçóëüòàòà
        double Result = CountValidNumbers(Base, DigitCount);

        // Âûâîä ðåçóëüòàòà
        std::cout << "Êîëè÷åñòâî äîïóñòèìûõ ÷èñåë: " << Result << std::endl;
    }
    catch (const std::runtime_error& Exception)
    {
        std::cerr << Exception.what() << std::endl;
        return 1;
    }
    catch (const std::exception& Exception)
    {
        std::cerr << "Íåèçâåñòíàÿ îøèáêà: " << Exception.what() << std::endl;
        return 2;
    }

    return 0;
}
