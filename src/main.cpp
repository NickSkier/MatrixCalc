#include <iostream>
#include <iomanip>
#include <vector>

class Matrix{
	private:
		size_t rows;
		size_t cols;
		std::vector<std::vector<double>> matrix;
		static double errorValue;
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
				std::cerr << "Index out of bounds.";
				return errorValue;
			}
			return matrix[row][col];
		}

		double& operator()(size_t row, size_t col) {
			if (row >= rows || col >= cols) {
				std::cerr << "Index out of bounds.";
				return errorValue;
			}
			return matrix[row][col];
		}

		Matrix operator+(const Matrix& other) const {
			if (rows != other.rows || cols != other.cols) {
				std::cerr << "Matrix dimensions must match for addition.";
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

		Matrix operator-(const Matrix& other) const {
			if (rows != other.rows || cols != other.cols) {
				std::cerr << "Matrix dimensions must match for subtract.";
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

		Matrix operator*(const Matrix& other) const {
			if (cols != other.rows) {
				std::cerr << "Matrix dimensions must match for multiplication.";
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

		Matrix transpose() const {
			Matrix result(cols, rows);
			for (size_t i = 0; i < rows; ++i) {
				for (size_t j = 0; j < cols; ++j) {
				    result(j, i) = matrix[i][j];
				}
			}
			return result;
		}

		Matrix submatrix(size_t excludeRow, size_t excludeCol) const {
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

		void swapRows(size_t row1, size_t row2) {
		    if (row1 >= rows || row2 >= rows) {
		        std::cerr << "Row index out of bounds.";
		        return;
		    }
		    std::swap(matrix[row1], matrix[row2]);
		}

		double determinant() const {
		    if (rows != cols) {
		        std::cerr << "Determinant is defined only for square matrices.";
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

		Matrix inverse() const {
		    double det = determinant();
		    if (det == 0) {
		        	std::cerr << "Matrix is singular and cannot be inverted.";
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

		size_t rank() const {
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

		Matrix power(int exp) const {
		    if (rows != cols) {
		        std::cerr << "Matrix exponentiation is defined only for square matrices.";
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

double Matrix::errorValue = 0.0;

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

	// Возведение в степень
	std::cout << "A^2:" << std::endl;
	Matrix A_squared = A.power(2);
	A_squared.print();
	std::cout << "A^3:" << std::endl;
	Matrix A_cubed = A.power(3);
	A_cubed.print();
	std::cout << std::endl;

	double A_det = A.determinant();
	std::cout << "Determinant of A: " << A_det << std::endl;
	std::cout << std::endl;

	Matrix A_inv = A.inverse();
	std::cout << "Inverse of A:" << std::endl;
	A_inv.print();
	std::cout << std::endl;

	size_t A_rank = A.rank();
	std::cout << "Rank of A: " << A_rank << std::endl;
	std::cout << std::endl;

	Matrix D(3, 3);
	D(0, 0) = 6; D(0, 1) = 1; D(0, 2) = 1;
	D(1, 0) = 4; D(1, 1) = -2; D(1, 2) = 5;
	D(2, 0) = 2; D(2, 1) = 8; D(2, 2) = 7;

	std::cout << "Matrix D:" << std::endl;
	D.print();

	double D_det = D.determinant();
	std::cout << "Determinant of D: " << D_det << std::endl;
	std::cout << std::endl;

	Matrix I(3, 3);
	I(0, 0) = 2; I(0, 1) = -1; I(0, 2) = 0;
	I(1, 0) = -1; I(1, 1) = 2; I(1, 2) = -1;
	I(2, 0) = 0; I(2, 1) = -1; I(2, 2) = 2;

	std::cout << "Matrix I:" << std::endl;
	I.print();

	Matrix I_inv = I.inverse();
	std::cout << "Inverse of I:" << std::endl;
	I_inv.print();
	std::cout << std::endl;

	Matrix R(3, 4);
	R(0, 0) = 1; R(0, 1) = 2; R(0, 2) = 3; R(0, 3) = 4;
	R(1, 0) = 2; R(1, 1) = 4; R(1, 2) = 6; R(1, 3) = 8;
	R(2, 0) = 3; R(2, 1) = 6; R(2, 2) = 9; R(2, 3) = 12;

	std::cout << "Matrix R:" << std::endl;
	R.print();

	size_t R_rank = R.rank();
	std::cout << "Rank of R: " << R_rank << std::endl;
	std::cout << std::endl;

	return 0;
}
