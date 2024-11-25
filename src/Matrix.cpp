#include "Matrix.h"

// Инициализация статической переменной
double Matrix::errorValue = 0.0;

// Конструктор квадратной матрицы
Matrix::Matrix(size_t size) : rows(size), cols(size) {
	matrix.resize(size, std::vector<double>(size, 0));
	for (size_t i = 0; i < size; ++i) {
		matrix[i][i] = 1.0;
	}
}

// Конструктор произвольной матрицы
Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
	matrix.resize(rows);
	for (size_t i = 0; i < rows; ++i) {
		matrix[i].resize(cols);
	}
}

// Оператор доступа для константного объекта
const double& Matrix::operator()(size_t row, size_t col) const {
	if (row >= rows || col >= cols) {
		std::cerr << "Index out of bounds.";
		return errorValue;
	}
	return matrix[row][col];
}

// Оператор доступа
double& Matrix::operator()(size_t row, size_t col) {
	if (row >= rows || col >= cols) {
		std::cerr << "Index out of bounds.";
		return errorValue;
	}
	return matrix[row][col];
}

// Сложение матриц
Matrix Matrix::operator+(const Matrix& other) const {
	if (rows != other.rows || cols != other.cols) {
		std::cerr << "Matrix dimensions must match for addition." << std::endl;
		return Matrix(rows, cols);
	}
	Matrix result(rows, cols);
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			result(i, j) = matrix[i][j] + other(i, j);
		}
	}
	return result;
}

// Вычитание матриц
Matrix Matrix::operator-(const Matrix& other) const {
	if (rows != other.rows || cols != other.cols) {
		std::cerr << "Matrix dimensions must match for subtract." << std::endl;
		return Matrix(rows, cols);
	}
	Matrix result(rows, cols);
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			result(i, j) = matrix[i][j] - other(i, j);
		}
	}
	return result;
}

// Умножение матриц
Matrix Matrix::operator*(const Matrix& other) const {
	if (cols != other.rows) {
		std::cerr << "Matrix dimensions must match for multiplication." << std::endl;
		return Matrix(rows, cols);
	}
	Matrix result(rows, other.cols);
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < other.cols; ++j) {
			for (size_t k = 0; k < cols; ++k) {
				result(i, j) += matrix[i][k] * other(k, j);
			}
		}
	}
	return result;
}

// Транспонирование
Matrix Matrix::transpose() const {
	Matrix result(cols, rows);
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			result(j, i) = matrix[i][j];
		}
	}
	return result;
}

// Подматрица
Matrix Matrix::submatrix(size_t excludeRow, size_t excludeCol) const {
	Matrix result(rows - 1, cols - 1);
	size_t rowOffset = 0;
	for (size_t i = 0; i < rows; ++i) {
		if (i == excludeRow) {
			rowOffset = 1;
			continue;
		}
		size_t colOffset = 0;
		for (size_t j = 0; j < cols; ++j) {
			if (j == excludeCol) {
				colOffset = 1;
				continue;
			}
		result(i - rowOffset, j - colOffset) = matrix[i][j];
		}
	}
	return result;
}

// Обмен строк
void Matrix::swapRows(size_t row1, size_t row2) {
    if (row1 >= rows || row2 >= rows) {
        std::cerr << "Row index out of bounds.";
        return;
    }
    std::swap(matrix[row1], matrix[row2]);
}

// Определитель
double Matrix::determinant() const {
    if (rows != cols) {
        std::cerr << "Determinant is defined only for square matrices." << std::endl;
        return 0.0;
    }
    if (rows == 1) {
        return matrix[0][0];
    }
    if (rows == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    double det = 0.0;
    for (size_t j = 0; j < cols; ++j) {
        det += (j % 2 == 0 ? 1 : -1) * matrix[0][j] * submatrix(0, j).determinant();
    }
    return det;
}

// Обратная матрица
Matrix Matrix::inverse() const {
    double det = determinant();
    if (det == 0) {
        	std::cerr << "Matrix is singular and cannot be inverted." << std::endl;
        	return Matrix(rows, cols);
    }
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(j, i) = ((i + j) % 2 == 0 ? 1 : -1) * submatrix(i, j).determinant() / det;
        }
    }
    return result;
}

// Ранг матрицы
size_t Matrix::rank() const {
    Matrix temp = *this;
    size_t rank = 0;
    for (size_t row = 0; row < rows; ++row) {
        if (temp(row, row) != 0) {
            ++rank;
            for (size_t r = row + 1; r < rows; ++r) {
                double factor = temp(r, row) / temp(row, row);
                for (size_t c = 0; c < cols; ++c) {
                    temp(r, c) -= factor * temp(row, c);
                }
            }
        }
    }
    return rank;
}

// Возведение в степень
Matrix Matrix::power(int exp) const {
    if (rows != cols) {
        std::cerr << "Matrix exponentiation is defined only for square matrices." << std::endl;
    }
    if (exp == 0) {
        return Matrix(rows); // Identity matrix
    }
    if (exp < 0) {
        return inverse().power(-exp);
    }
    Matrix result = *this;
    Matrix base = *this;
    for (int i = 1; i < exp; ++i) {
        result = result * base;
    }
    return result;
}

// Заполнение матрицы
void Matrix::fill() {
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			matrix[i][j] = i * cols + j;
		}
	}
}

// Вывод матрицы на экран
void Matrix::print() {
	for (const auto& row : matrix) {
		std::cout << "|";
		for (double elem : row) {
			std::cout << std::setw(2) << elem << " ";
		}
		std::cout << "|" << std::endl;
	}
}
