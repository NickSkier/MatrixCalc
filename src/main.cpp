#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <locale>
#include "Matrix.h"

// Функция для создания матрицы
Matrix createMatrix() {
    size_t rows, cols;
    std::cout << "Введите количество строк: ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов: ";
    std::cin >> cols;

    Matrix matrix(rows, cols);

    int fillChoice;
    std::cout << "Выберите способ заполнения матрицы:\n";
    std::cout << "1. Автоматическое заполнение\n";
    std::cout << "2. Ручной ввод\n";
    std::cout << "Ваш выбор: ";
    std::cin >> fillChoice;

    if (fillChoice == 1) {
        matrix.fillRandom();
    } else if (fillChoice == 2) {
        std::cout << "Введите элементы матрицы:\n";
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                double value;
                std::cout << "Элемент [" << i << "][" << j << "]: ";
                std::cin >> value;
                matrix(i, j) = value;
            }
        }
    }

    return matrix;
}

// Главное меню
void showMainMenu() {
    std::cout << "\n--- Калькулятор матриц ---\n";
    std::cout << "1. Создать матрицу\n";
    std::cout << "2. Вывести матрицу\n";
    std::cout << "3. Транспонировать матрицу\n";
    std::cout << "4. Сложение матриц\n";
    std::cout << "5. Вычитание матриц\n";
    std::cout << "6. Умножение матриц\n";
    std::cout << "7. Умножение матрицы на скаляр\n";
    std::cout << "8. Деление матрицы на скаляр\n";
    std::cout << "9. Возведение матрицы в степень\n";
    std::cout << "10. Вычисление определителя\n";
    std::cout << "11. Вычисление обратной матрицы\n";
    std::cout << "12. Вычисление ранга матрицы\n";
    std::cout << "20. Настройки\n";
    std::cout << "0. Выход\n";
    std::cout << "Введите номер операции: ";
}

std::vector<int> settings = {1, 4};
//  Меню настроек
void showSettingsMenu() {
    std::cout << "\n--- Настройки калькулятора ---\n";
    std::cout << "1. Сохранять результаты операций : " << settings[0] << std::endl;
    std::cout << "2. Чисел после запятой : " << settings[1] << std::endl;
    std::cout << "0. Вернуться\n";
    std::cout << "Введите номер настроек: ";
}

int main() {
	setlocale(LC_ALL, "Russian");

	// Вектор для хранения матриц
    std::vector<std::unique_ptr<Matrix>> matrices;

	int choice;
    do {
        showMainMenu();
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    matrices.emplace_back(std::make_unique<Matrix>(createMatrix()));
                    std::cout << "Матрица создана. Индекс: " << matrices.size() - 1 << std::endl;
                    break;
                }
                case 2: {
                    size_t index;
                    std::cout << "Введите индекс матрицы: ";
                    std::cin >> index;
                    if (index < matrices.size()) {
                        std::cout << "Матрица [" << index << "]:\n";
                        matrices[index]->print();
                    } else {
                        std::cout << "Неверный индекс матрицы.\n";
                    }
                    break;
                }
                case 3: {
                    size_t index;
                    std::cout << "Введите индекс матрицы: ";
                    std::cin >> index;
                    if (index < matrices.size()) {
                        Matrix transposed = matrices[index]->transpose();
                        std::cout << "Транспонированная матрица:\n";
                        transposed.print();
		                if (settings[0] == 1) {
		                    matrices.emplace_back(std::make_unique<Matrix>(transposed));
		                    std::cout << "Матрица сохранена. Индекс: " << matrices.size() - 1 << std::endl;
		                }
                    } else {
                        std::cout << "Неверный индекс матрицы.\n";
                    }
                    break;
                }
                case 4: {
                    size_t index1, index2;
                    std::cout << "Введите индекс первой матрицы: ";
                    std::cin >> index1;
                    std::cout << "Введите индекс второй матрицы: ";
                    std::cin >> index2;
                    if (index1 < matrices.size() && index2 < matrices.size()) {
                        Matrix sum = *matrices[index1] + *matrices[index2];
                        std::cout << "Результат сложения:\n";
                        sum.print();
		                if (settings[0] == 1) {
		                    matrices.emplace_back(std::make_unique<Matrix>(sum));
		                    std::cout << "Матрица сохранена. Индекс: " << matrices.size() - 1 << std::endl;
		                }
                    } else {
                        std::cout << "Неверные индексы матриц.\n";
                    }
                    break;
                }
                case 5: {
                    size_t index1, index2;
                    std::cout << "Введите индекс первой матрицы: ";
                    std::cin >> index1;
                    std::cout << "Введите индекс второй матрицы: ";
                    std::cin >> index2;
                    if (index1 < matrices.size() && index2 < matrices.size()) {
                        Matrix diff = *matrices[index1] - *matrices[index2];
                        std::cout << "Результат вычитания:\n";
                        diff.print();
		                if (settings[0] == 1) {
		                    matrices.emplace_back(std::make_unique<Matrix>(diff));
		                    std::cout << "Матрица сохранена. Индекс: " << matrices.size() - 1 << std::endl;
		                }
                    } else {
                        std::cout << "Неверные индексы матриц.\n";
                    }
                    break;
                }
                case 6: {
                    size_t index1, index2;
                    std::cout << "Введите индекс первой матрицы: ";
                    std::cin >> index1;
                    std::cout << "Введите индекс второй матрицы: ";
                    std::cin >> index2;
                    if (index1 < matrices.size() && index2 < matrices.size()) {
                        Matrix product = *matrices[index1] * *matrices[index2];
                        std::cout << "Результат умножения:\n";
                        product.print();
		                if (settings[0] == 1) {
		                    matrices.emplace_back(std::make_unique<Matrix>(product));
		                    std::cout << "Матрица сохранена. Индекс: " << matrices.size() - 1 << std::endl;
		                }
                    } else {
                        std::cout << "Неверные индексы матриц.\n";
                    }
                    break;
                }
                case 7: {
                    size_t index;
                    double scalar;
                    std::cout << "Введите индекс матрицы: ";
                    std::cin >> index;
                    std::cout << "Введите скаляр: ";
                    std::cin >> scalar;
                    if (index < matrices.size() && matrices[index]) {
                        Matrix scaled = *matrices[index] * scalar;
                        std::cout << "Результат умножения на скаляр:\n";
                        scaled.print();
		                if (settings[0] == 1) {
		                    matrices.emplace_back(std::make_unique<Matrix>(scaled));
		                    std::cout << "Матрица сохранена. Индекс: " << matrices.size() - 1 << std::endl;
		                }
                    } else {
                        std::cout << "Неверный индекс матрицы.\n";
                    }
                    break;
                }
                case 8: {
                    size_t index;
                    double scalar;
                    std::cout << "Введите индекс матрицы: ";
                    std::cin >> index;
                    std::cout << "Введите скаляр: ";
                    std::cin >> scalar;
                    if (index < matrices.size() && matrices[index]) {
                        if (scalar != 0) {
                            Matrix scaled = *matrices[index] / scalar;
                            std::cout << "Результат деления на скаляр:\n";
                            scaled.print();
		                    if (settings[0] == 1) {
		                        matrices.emplace_back(std::make_unique<Matrix>(scaled));
		                        std::cout << "Матрица сохранена. Индекс: " << matrices.size() - 1 << std::endl;
		                    }
                        } else {
                            std::cout << "Ошибка: деление на ноль.\n";
                        }
                    } else {
                        std::cout << "Неверный индекс матрицы.\n";
                    }
                    break;
                }
                case 9: {
                    size_t index;
                    int power;
                    std::cout << "Введите индекс матрицы: ";
                    std::cin >> index;
                    std::cout << "Введите степень: ";
                    std::cin >> power;
                    if (index < matrices.size() && matrices[index]) {
                        Matrix powered = matrices[index]->power(power);
                        std::cout << "Результат возведения в степень:\n";
                        powered.print();
		                if (settings[0] == 1) {
		                    matrices.emplace_back(std::make_unique<Matrix>(powered));
		                    std::cout << "Матрица сохранена. Индекс: " << matrices.size() - 1 << std::endl;
		                }
                    } else {
                        std::cout << "Неверный индекс матрицы.\n";
                    }
                    break;
                }
                case 10: {
                    size_t index;
                    std::cout << "Введите индекс матрицы: ";
                    std::cin >> index;
                    if (index < matrices.size() && matrices[index]) {
                        double det = matrices[index]->determinant();
                        std::cout << "Определитель матрицы: " << det << std::endl;
                    } else {
                        std::cout << "Неверный индекс матрицы.\n";
                    }
                    break;
                }
                case 11: {
                    size_t index;
                    std::cout << "Введите индекс матрицы: ";
                    std::cin >> index;
                    if (index < matrices.size() && matrices[index]) {
                        Matrix inv = matrices[index]->inverse();
                        std::cout << "Обратная матрица:\n";
                        inv.print();
		                if (settings[0] == 1) {
		                    matrices.emplace_back(std::make_unique<Matrix>(inv));
		                    std::cout << "Матрица сохранена. Индекс: " << matrices.size() - 1 << std::endl;
		                }
                    } else {
                        std::cout << "Неверный индекс матрицы.\n";
                    }
                    break;
                }
                case 12: {
                    size_t index;
                    std::cout << "Введите индекс матрицы: ";
                    std::cin >> index;
                    if (index < matrices.size() && matrices[index]) {
                        size_t rank = matrices[index]->rank();
                        std::cout << "Ранг матрицы: " << rank << std::endl;
                    } else {
                        std::cout << "Неверный индекс матрицы.\n";
                    }
                    break;
                }
                case 20: {
		            do {
		                showSettingsMenu();
		                std::cin >> choice;
		                switch (choice) {
		                case 1: {
		                    std::cout << "Сохранять ли результаты операций как новые матрицы с отдельным индексом? 1 (Да), 0 (Нет): ";
		                    std::cin >> settings[0];
		                    break;
		                }
		                case 2: {
		                    std::cout << "Сколько чисел после запятой отображать: ";
		                    std::cin >> settings[1];
		                    break;
		                }
		                case 0:
		                    std::cout << "Выход из настроек\n";
		                    break;
		                default:
		                    std::cout << "Неверный выбор. Попробуйте снова.\n";
		                }
		            } while (choice != 0);
					choice = -1;
                		break;
            }
                case 0:
                    std::cout << "Программа завершена.\n";
                    break;
                default:
                    std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

    } while (choice != 0);

	return 0;
}
