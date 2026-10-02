#include "HeaderTask01.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    try
    {
        // FIX_ME: переменные N и Z не объявлены, из-за этого код не компилируется
        // int N, Z;
        int NumArtifacts;
        int MinRequiredWeight;

        // FIX_ME: имя файла не указано, поэтому ifstream не может открыть несуществующий файл
        // ifstream f1("археолог.txt");
        std::ifstream ArtifactInput("artifacts.txt");

        // FIX_ME: нет проверки на успешное открытие файла — программа продолжит выполнение даже если файла нет
        if (!ArtifactInput.is_open())
        {
            throw std::runtime_error("Ошибка: не удалось открыть файл 'artifacts.txt'");
        }

        // FIX_ME: не читается первая строка файла, поэтому нельзя распарсить N и Z
        std::string FirstLine;
        if (!std::getline(ArtifactInput, FirstLine))
        {
            throw std::runtime_error("Ошибка: файл пуст или не удалось прочитать первую строку");
        }

        // FIX_ME: отсутствует проверка строки на недопустимые символы — можно получить мусор при парсинге
        if (ContainsInvalidChars(FirstLine))
        {
            throw std::runtime_error("Ошибка: в первой строке найдены недопустимые символы (разрешены цифры, пробелы и знаки минус)");
        }

        // FIX_ME: попытка прочитать N и Z без предварительной подготовки stringstream — данные не будут считаны
        std::stringstream FirstStream(FirstLine);
        if (!(FirstStream >> NumArtifacts >> MinRequiredWeight))
        {
            throw std::runtime_error("Ошибка: не удалось прочитать значения N и Z из первой строки");
        }

        // FIX_ME: не читается вторая строка (веса артефактов), поэтому дальше код работает с неинициализированными данными
        std::string SecondLine;
        if (!std::getline(ArtifactInput, SecondLine))
        {
            throw std::runtime_error("Ошибка: не удалось прочитать вторую строку с весами");
        }

        // FIX_ME: отсутствует валидация второй строки — при наличии мусора в строке парсинг сломается
        if (ContainsInvalidChars(SecondLine))
        {
            throw std::runtime_error("Ошибка: во второй строке найдены недопустимые символы");
        }

        // FIX_ME: векторы weight и nalog объявлены неправильно
        // vector<int> weight(NumArtifacts + 1);
        // vector<int> nalog(NumArtifacts + 1);
        std::vector<int> ArtifactWeights(NumArtifacts + 1);
        std::vector<int> ArtifactTaxes(NumArtifacts + 1);

        // FIX_ME: циклы чтения весов и налогов закомментированы — данные не считываются, векторы остаются нулевыми
        // for (int i = 1; i <= NumArtifacts; i++) {
        //     ArtifactInput >> ArtifactWeights[i];
        // }
        // for (int i = 1; i <= NumArtifacts; i++) {
        //     ArtifactInput >> ArtifactTaxes[i];
        // }

        // FIX_ME: вместо чтения из файла нужно читать из второй строки через stringstream, иначе веса не будут считаны корректно
        std::stringstream SecondStream(SecondLine);
        for (int Index = 1; Index <= NumArtifacts; Index++)
        {
            if (!(SecondStream >> ArtifactWeights[Index]))
            {
                throw std::runtime_error("Ошибка: недостаточно значений весов в строке (ожидалось " +
                    std::to_string(NumArtifacts) + " значений)");
            }
        }

        // FIX_ME: не проверяется, что в строке весов нет лишних чисел — это может исказить дальнейший парсинг
        int ExtraValue;
        if (SecondStream >> ExtraValue)
        {
            throw std::runtime_error("Ошибка: в строке весов найдено лишнее значение после N чисел");
        }

        // FIX_ME: не читается третья строка (налоги), поэтому налоги остаются нулевыми и решение будет некорректным
        std::string ThirdLine;
        if (!std::getline(ArtifactInput, ThirdLine))
        {
            throw std::runtime_error("Ошибка: не удалось прочитать третью строку с налогами");
        }

        // FIX_ME: отсутствует валидация третьей строки — мусор в строке приведёт к неверному парсингу налогов
        if (ContainsInvalidChars(ThirdLine))
        {
            throw std::runtime_error("Ошибка: в третьей строке найдены недопустимые символы");
        }

        // FIX_ME: налоги не читаются из строки — вместо этого используются нули, что ломает логику задачи
        std::stringstream ThirdStream(ThirdLine);
        for (int Index = 1; Index <= NumArtifacts; Index++)
        {
            if (!(ThirdStream >> ArtifactTaxes[Index]))
            {
                throw std::runtime_error("Ошибка: недостаточно значений налогов в строке (ожидалось " +
                    std::to_string(NumArtifacts) + " значений)");
            }
        }

        // FIX_ME: не проверяется наличие лишних чисел в строке налогов — это может испортить состояние потока
        if (ThirdStream >> ExtraValue)
        {
            throw std::runtime_error("Ошибка: в строке налогов найдено лишнее значение после N чисел");
        }

        // FIX_ME: не проверяется, что после третьей строки нет значимых данных — лишние строки могут быть признаком некорректного файла
        std::string ExtraLine;
        if (std::getline(ArtifactInput, ExtraLine))
        {
            bool bIsEmpty = true;
            for (char Character : ExtraLine)
            {
                if (!isspace(static_cast<unsigned char>(Character)))
                {
                    bIsEmpty = false;
                    break;
                }
            }
            if (!bIsEmpty)
            {
                throw std::runtime_error("Ошибка: обнаружены лишние данные после третьей строки");
            }
        }

        // FIX_ME: переменная maxWeight не объявлена и не посчитана — нельзя корректно инициализировать DP-таблицу
        // int maxWeight = 0;
        int MaxWeight = 0;

        for (int Index = 1; Index <= NumArtifacts; Index++)
        {
            MaxWeight += ArtifactWeights[Index];
        }

        // FIX_ME: отсутствует проверка, что суммарный вес всех артефактов больше минимально требуемого — иначе задача не имеет решения
        if (MaxWeight <= MinRequiredWeight)
        {
            throw std::runtime_error("Ошибка: суммарный вес всех артефактов не превышает минимально требуемый");
        }

        // FIX_ME: DP-таблица инициализирована константой 10000000 вместо INT_MAX — это ненадёжно и может привести к ошибкам при больших значениях
        // std::vector<std::vector<int>> dp(NumArtifacts + 1, std::vector<int>(MaxWeight + 1, 10000000));
        std::vector<std::vector<int> > DPTable(NumArtifacts + 1, std::vector<int>(MaxWeight + 1, INT_MAX));

        DPTable[0][0] = 0;

        for (int ArtifactIndex = 1; ArtifactIndex <= NumArtifacts; ArtifactIndex++)
        {
            // FIX_ME: цикл по весам не реализован — DP-таблица не заполняется, решение не будет найдено
            // for (int s = 0; s <= MaxWeight; s++) 
            for (int CurrentWeight = 0; CurrentWeight <= MaxWeight; CurrentWeight++)
            {
                DPTable[ArtifactIndex][CurrentWeight] = DPTable[ArtifactIndex - 1][CurrentWeight];
                if (CurrentWeight >= ArtifactWeights[ArtifactIndex] &&
                    DPTable[ArtifactIndex - 1][CurrentWeight - ArtifactWeights[ArtifactIndex]] != INT_MAX)
                {
                    DPTable[ArtifactIndex][CurrentWeight] = std::min(
                        DPTable[ArtifactIndex][CurrentWeight],
                        DPTable[ArtifactIndex - 1][CurrentWeight - ArtifactWeights[ArtifactIndex]] + ArtifactTaxes[ArtifactIndex]
                    );
                }
            }
        }

        // FIX_ME: переменные minNalog и bestWeight не объявлены — нельзя найти оптимальное решение
        // int minNalog = INT_MAX;
        // int bestWeight = -1;
        int MinTax = INT_MAX;
        int BestWeight = -1;

        // FIX_ME: поиск оптимального веса не реализован — программа не найдёт решение даже при корректной DP-таблице
        // for (int s = MinRequiredWeight +1 ; s <= MaxWeight; s++) {
        //     if (DPTable[NumArtifacts][s] < MinTax) {
        //         MinTax = DPTable[NumArtifacts][s];
        //         BestWeight = s;
        //     }
        // }
        for (int CurrentWeight = MinRequiredWeight + 1; CurrentWeight <= MaxWeight; CurrentWeight++)
        {
            if (DPTable[NumArtifacts][CurrentWeight] < MinTax)
            {
                MinTax = DPTable[NumArtifacts][CurrentWeight];
                BestWeight = CurrentWeight;
            }
        }

        // FIX_ME: отсутствует проверка, что решение действительно найдено — можно вывести некорректные значения
        if (BestWeight == -1 || MinTax == INT_MAX)
        {
            throw std::runtime_error("Ошибка: не удалось подобрать набор артефактов, удовлетворяющий условию по весу");
        }

        std::cout << "Минимальный налог: " << MinTax << std::endl;
        std::cout << "Оптимальный вес: " << BestWeight << std::endl;
        std::cout << "Выбранные артефакты: ";

        FindAnswer(DPTable, NumArtifacts, BestWeight, ArtifactWeights, ArtifactTaxes);

        std::cout << std::endl;
        ArtifactInput.close();
    }
    catch (const std::runtime_error& Exception)
    {
        std::cerr << Exception.what() << std::endl;
        return 1;
    }
    catch (const std::exception& Exception)
    {
        std::cerr << "Неизвестная ошибка: " << Exception.what() << std::endl;
        return 2;
    }

    return 0;
}
