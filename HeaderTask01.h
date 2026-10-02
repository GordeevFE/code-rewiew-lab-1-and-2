//Археолог нашел N артефактов.Известны веса(сi) и налоговое бремя(di) находок.
//Нужно выбрать такое подмножество находок, чтобы их суммарный вес превысил Z кг, а их об
//щее налоговое бремя оказалось минимальным.Известно, что решение единственно.Укажите
//порядковые номера вещей, которые нужно взять.Исходный данные находятся в текстовом файле, 
//в первой строке указаны N и Z, а во второй строке значения весов(в кг), в третьей - величина
//налога по каждой находке.Вывести так же суммарный вес и общую ценность результата.


//FIX_ME: остуствует разделение на модули
#ifndef HeaderTask01
#define HeaderTask01

#include <iostream>
#include<fstream>
#include<vector>
#include <climits>  // для INT_MAX
#include <string>
#include <sstream> 

void FindAnswer(const std::vector<std::vector<int> >& InDPTable,
    int CurrentIndex, int CurrentWeight, std::vector<int>& InWeights, std::vector<int>& InTaxes);
bool ContainsInvalidChars(const std::string& InLine);

#endif // HeaderTask01
