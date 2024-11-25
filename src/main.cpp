#include <iostream>
#include <iomanip>
#include <vector>
#include "Matrix.h"

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
