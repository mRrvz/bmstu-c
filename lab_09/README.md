# Тесты для лабораторной работы №9

## Функциональные
### Негативные
in_1 - 4 - отрицательные размеры обоих матриц (строки столбцы)

in_5 - 6 - строка вместо числа (строки / столбцы)

in_7 - 8 - строка вместо очередного элемента матрицы

in_9 - 10 - отрицательные размеры степени

in_11 - 12 - строка вместо степени

### Позитивные
in_1 - две обычные матрицы, не приведенные к квадратному виду

in_2 - две матрицы, квадратного вида

in_3 - две единичные матрицы

in_4 - нулевые степени для матриц

in_5 - две матрицы 1х1

in_6 - одна матрицы 1х1

in_7 - одна нулевая матрица

## Модульные
Тестируемые функции: 
1. avg_columns_counter (подсчет среднего арифметического для заданного столбца)
2. max_rows_counter (поиск наибольшего числа в заданной строчке)
3. square_matrix (приведение матрицы к квадратному виду)
4. matrix_equalization (расширение первой матрицы до размера второй матрицы)
5. null_degree_checker (приведение матрицы к единичному виду, если ее степень равна нулю)


![Alt text](https://sun9-4.userapi.com/c858324/v858324967/7653f/xvN0eRrJcLI.jpg "CUnitTableTests")