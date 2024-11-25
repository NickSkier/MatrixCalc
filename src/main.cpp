#include <iostream>
#include <iomanip>
#include <vector>

class Matrix{
	private:
		size_t rows;
		size_t cols;
		std::vector<std::vector<double>> matrix;
	public:
		Matrix(size_t size) : rows(size), cols(size) {
			matrix.resize(size, std::vector<double>(size, 0));
			for (size_t i = 0; i < size; ++i) {
				matrix[i][i] = 1.0;
			}
		}

		Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
			matrix.resize(rows);
			for (size_t i = 0; i < rows; ++i) {
				matrix[i].resize(cols);
			}
		}

	const double& operator()(size_t row, size_t col) const {
		if (row >= rows || col >= cols) {
			throw std::out_of_range("Index out of bounds.");
		}
		return matrix[row][col];
	}

	double& operator()(size_t row, size_t col) {
		if (row >= rows || col >= cols) {
			throw std::out_of_range("Index out of bounds.");
		}
		return matrix[row][col];
	}

	Matrix operator+(const Matrix& other) const {
		if (rows != other.rows || cols != other.cols) {
			throw std::invalid_argument("Matrix dimensions must match for addition.");
		}
		Matrix result(rows, cols);
		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < cols; ++j) {
				result(i, j) = matrix[i][j] + other(i, j);
			}
		}
		return result;
	}

	Matrix operator-(const Matrix& other) const {
		if (rows != other.rows || cols != other.cols) {
			throw std::invalid_argument("Matrix dimensions must match for subtract.");
		}
		Matrix result(rows, cols);
		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < cols; ++j) {
				result(i, j) = matrix[i][j] - other(i, j);
			}
		}
		return result;
	}

	Matrix operator*(const Matrix& other) const {
		if (cols != other.rows) {
			throw std::invalid_argument("Matrix dimensions must match for multiplication.");
		}
		Matrix result(rows, other.cols);
		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < other.cols; ++j) {
				//std::cout << "m:" << i << " " << "o:"<< j << std::endl;
				for (size_t k = 0; k < cols; ++k) {
					result(i, j) += matrix[i][k] * other(k, j);
					//std::cout << matrix[i][k] << " " << other(k, j) << " " << temp << std::endl;
				}
			}
		}
		return result;
	}

	Matrix transpose() const {
		Matrix result(cols, rows);
		for (size_t i = 0; i < rows; ++i) {
		    for (size_t j = 0; j < cols; ++j) {
		        result(j, i) = matrix[i][j];
		    }
		}
		return result;
	}

	void fill() {
		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < cols; ++j) {
				matrix[i][j] = i * cols + j;
			}
		}
	}

	void print() {
		for (const auto& row : matrix) {
			std::cout << "|";
			for (double elem : row) {
				std::cout << std::setw(2) << elem << " ";
			}
			std::cout << "|" << std::endl;
		}
	}

};

int main() {

	Matrix A(3, 3);
	A.fill();
	std::cout << "Matrix A:" << std::endl;
	A.print();

	// Транспонирование
	std::cout << std::endl << "Transposed A:" << std::endl;
	Matrix T = A.transpose();
	T.print();
	std::cout << std::endl;

	// Сложение
	std::cout << "A + T:" << std::endl;
	Matrix A2 = A + T;
	A2.print();
	std::cout << std::endl;

	// Вычитание
	std::cout << "A - A:" << std::endl;
	A2 = A - A;
	A2.print();
	std::cout << std::endl;

	// Умножение
	Matrix B(2, 3), C(3, 5);
	B.fill();
	C.fill();
	B.print();
	std::cout << std::endl;
	C.print();
	std::cout << std::endl;

	std::cout << "B * C:" << std::endl;
	Matrix BC = B * C;
	BC.print();
	std::cout << std::endl;

	return 0;
}
