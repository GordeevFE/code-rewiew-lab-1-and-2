#include "HeaderTask02.h"

//FIX_ME: заменяем использование std
//using namespace std;

bool IsValidNumber(int InValue)
{
    return InValue >= 0 && InValue <= 100;
}

//FIX_ME: неправильное использование
//int main() {
int main()
{
    setlocale(LC_ALL, "ru");

    try
    {
        //FIX_ME: неправильное название файла
        //ifstream input("input.txt");
        //ofstream output("output.txt");
        std::ifstream InputFile("input.txt");
        std::ofstream OutputFile("output.txt");

        //FIX_ME: отсутствует проверка наличия файла
        if (!InputFile.is_open())
        {
            throw std::runtime_error("Ошибка: не удалось открыть файл 'input.txt'");
        }

        if (!OutputFile.is_open())
        {
            throw std::runtime_error("Ошибка: не удалось открыть файл 'output.txt'");
        }

        // Чтение первой строки с размером поля
        std::string FirstLine;
        if (!std::getline(InputFile, FirstLine))
        {
            throw std::runtime_error("Ошибка: файл пуст или не удалось прочитать первую строку");
        }

        // Проверка первой строки на недопустимые символы
        if (ContainsInvalidChars(FirstLine))
        {
            throw std::runtime_error("Ошибка: первая строка содержит недопустимые символы (разрешены только цифры, пробелы и знак минус)");
        }

        //FIX_ME: неправильное имя переменной
        //int N;
        int MatrixSize;

        // Парсинг первой строки
        std::stringstream FirstStream(FirstLine);
        if (!(FirstStream >> MatrixSize))
        {
            throw std::runtime_error("Ошибка: не удалось прочитать размер поля из первой строки");
        }

        //FIX_ME: неправильное название переменной
        //if (MatrixSize <= 1 || MatrixSize >= 80) {
        if (MatrixSize <= 1 || MatrixSize >= 80)
        {
            throw std::runtime_error("Ошибка: недопустимый размер поля. Должно быть 1 < N < 80. Получено: " +
                std::to_string(MatrixSize));
        }

        //FIX_ME: неправильное имя массива
        //vector<vector<int>> board(MatrixSize, vector<int>(MatrixSize));
        std::vector<std::vector<int>> GameBoard(MatrixSize, std::vector<int>(MatrixSize));

        // Чтение строк с числами на поле
        for (int RowIndex = 0; RowIndex < MatrixSize; ++RowIndex)
        {
            std::string CurrentLine;
            if (!std::getline(InputFile, CurrentLine))
            {
                throw std::runtime_error("Ошибка: не удалось прочитать строку " +
                    std::to_string(RowIndex + 1) + " с данными поля");
            }

            // Проверка строки на недопустимые символы
            if (ContainsInvalidChars(CurrentLine))
            {
                throw std::runtime_error("Ошибка: строка " + std::to_string(RowIndex + 1) +
                    " содержит недопустимые символы");
            }

            std::stringstream LineStream(CurrentLine);

            for (int ColIndex = 0; ColIndex < MatrixSize; ++ColIndex)
            {
                if (!(LineStream >> GameBoard[RowIndex][ColIndex]))
                {
                    throw std::runtime_error("Ошибка: недостаточно данных в строке " +
                        std::to_string(RowIndex + 1) + " (ожидалось " +
                        std::to_string(MatrixSize) + " чисел)");
                }

                // Проверка, что число не превышает 100
                if (!IsValidNumber(GameBoard[RowIndex][ColIndex]))
                {
                    throw std::runtime_error("Ошибка: число " + std::to_string(GameBoard[RowIndex][ColIndex]) +
                        " в позиции [" + std::to_string(RowIndex + 1) + "][" +
                        std::to_string(ColIndex + 1) + "] превышает допустимое значение 100");
                }
            }

            // Проверка, что не осталось лишних данных в строке
            int ExtraValue;
            if (LineStream >> ExtraValue)
            {
                throw std::runtime_error("Ошибка: в строке " + std::to_string(RowIndex + 1) +
                    " больше чисел, чем ожидалось");
            }
        }

        // Проверка, что в файле нет лишних строк
        std::string ExtraLine;
        if (std::getline(InputFile, ExtraLine))
        {
            // Проверяем пустая ли строка или содержит данные
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
                throw std::runtime_error("Ошибка: файл содержит лишние данные после строк с числами");
            }
        }

        //FIX_ME: неправильное имя массива
        //vector<vector<int>> dp(MatrixSize, vector<int>(MatrixSize, 0));
        std::vector<std::vector<int>> DPTable(MatrixSize, std::vector<int>(MatrixSize, 0));

        // Начальная позиция (нижний левый угол)
        DPTable[MatrixSize - 1][0] = GameBoard[MatrixSize - 1][0];

        // Заполнение первого столбца (движение только вверх)
        for (int RowIndex = MatrixSize - 2; RowIndex >= 0; --RowIndex)
        {
            DPTable[RowIndex][0] = DPTable[RowIndex + 1][0] + GameBoard[RowIndex][0];
        }

        // Заполнение последней строки (движение только вправо)
        for (int ColIndex = 1; ColIndex < MatrixSize; ++ColIndex)
        {
            DPTable[MatrixSize - 1][ColIndex] = DPTable[MatrixSize - 1][ColIndex - 1] + GameBoard[MatrixSize - 1][ColIndex];
        }

        // Заполнение остальной части (движение вверх или вправо)
        for (int RowIndex = MatrixSize - 2; RowIndex >= 0; --RowIndex)
        {
            for (int ColIndex = 1; ColIndex < MatrixSize; ++ColIndex)
            {
                DPTable[RowIndex][ColIndex] = std::min(DPTable[RowIndex + 1][ColIndex],
                    DPTable[RowIndex][ColIndex - 1]) +
                    GameBoard[RowIndex][ColIndex];
            }
        }

        // Запись результата в выходной файл
        OutputFile << DPTable[0][MatrixSize - 1];

        // Проверка, что запись прошла успешно
        if (!OutputFile.good())
        {
            throw std::runtime_error("Ошибка: не удалось записать результат в выходной файл");
        }

        std::cout << "Минимальное " << DPTable[0][MatrixSize - 1] << " значение в файле" << std::endl;

        InputFile.close();
        OutputFile.close();
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
