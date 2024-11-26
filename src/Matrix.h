#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

class Matrix {
private:
    size_t rows;
    size_t cols;
    std::vector<std::vector<double>> matrix;
public:
    Matrix(size_t size);              	// Конструктор для квадратной матрицы
    Matrix(size_t rows, size_t cols);  	// Конструктор для матрицы произвольного размера
	~Matrix();							// Пустой деструктор

    const double& operator()(size_t row, size_t col) const; // Оператор доступа (для константного объекта)
    double& operator()(size_t row, size_t col);             // Оператор доступа

    Matrix operator+(const Matrix& other) const; // Сложение матриц
    Matrix operator-(const Matrix& other) const; // Вычитание матриц
    Matrix operator*(const Matrix& other) const; // Умножение матриц
	Matrix operator*(double scalar) const; // Умножение матрицы на скаляр
	Matrix operator/(double scalar) const; // Деление матрицы на скаляр

    Matrix transpose() const;        // Транспонирование
    Matrix submatrix(size_t excludeRow, size_t excludeCol) const; // Подматрица
    void swapRows(size_t row1, size_t row2); // Обмен строк
    double determinant() const;      // Определитель
    Matrix inverse() const;          // Обратная матрица
    size_t rank() const;             // Ранг матрицы
    Matrix power(int exp) const;     // Возведение в степень

    void fill();  								// Заполнение матрицы
	void fillRandom(int min = 0, int max = 100);	// Заполнение матрицы случайными числами
    void print(int precionSize = 4); 			// Вывод матрицы на экран
};
