// Формула размещений с повторениями: 
// A(--k, n) = n^k.

// Формула сочетаний с повторениями:
// С(--k, n) = C(k, k+n-1) = (k+n-1)!/((n-1)!*k!)
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void generateCombinationsRecursive(vector<vector<int>>& variants, vector<int>& combination, int numValues, int index = 0, int minIndex = 0) {

    //Базовый случай: если достигли конца комбинации, записываем её
    if (index == combination.size())
    {
        variants.push_back(combination);
        return;
    }

    // Рекурсивно генерируем значения для текущей ячейки
    for (size_t i = minIndex; i < numValues; i++)
    {
        combination[index] = i;
        generateCombinationsRecursive(variants, combination, numValues, index + 1, i);
    }
}

void generateCombinations_vRecur(vector<vector<int>>& variants, int numCells, int numValues) {
    vector<int> combination(numCells, 0);                               // Создаём вектор для хранения одной текущей комбинации
    generateCombinationsRecursive(variants, combination, numValues);    // Рекурсия
}

void generateCombinations_vCycle(vector<vector<int>>& variants, int numCells, int numValues) {

    std::vector<int> combination(numCells, 0); // Создаем вектор для хранения комбинации
    while (true) {

        // Записываем текущую комбинацию
        variants.push_back(combination);

        // Увеличиваем значение в текущей позиции
        int index = numCells - 1;
        while (index >= 0 && combination[index] == (index >= 1?combination[index-1]: numValues - 1)) {
            combination[index] = 0;
            index--;
        }

        // Если достигли конца комбинаций, завершаем цикл
        if (index < 0) {
            break;
        }

        // Увеличиваем значение в следующей позиции
        combination[index]++;
    }
}

bool comparerDesc(const vector<int>& o1, const vector<int>& o2){
    for (int i = (o1.size() < o2.size() ? o1.size() : o2.size()) - 1; i >= 0; i--)
    {
        if (o1[i] != o2[i])
        {
            return o1[i] < o2[i];
        }
    }
    return true;
}

void printComparing(const vector<vector<int>>& var1, const vector<vector<int>>& var2) {
    string out;
    for (size_t i = 0; i < (var1.size() < var2.size() ? var1.size() : var2.size()); i++)
    {
        for (auto var : var1[i]) {
            out += (var < 10 ? " " + to_string(var) : to_string(var)) + " ";
        }
        out += " = ";
        for (auto var : var2[i]) {
            out += (var < 10 ? " " + to_string(var) : to_string(var)) + " ";
        }
        out += '\n';
    }
    cout << out << endl;
}

int main()
{
    int numCells = 4;
    int numValues = 9;

    // Создаём векторы для хранения вариантов
    vector<vector<int>> variants1, variants2; 

    // Заполняем векторы
    generateCombinations_vRecur(variants1, numCells, numValues);
    generateCombinations_vCycle(variants2, numCells, numValues);

    // Сортируем векторы
    sort(variants1.begin(), variants1.end());
    sort(variants2.begin(), variants2.end(), comparerDesc);

    // Выводим таблицу сравнения
    printComparing(variants1, variants2);

    return 0;
}
