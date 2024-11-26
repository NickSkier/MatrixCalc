# MatrixCalc

Simple CLI matrix calculator in C++

## Features

The `Matrix` class provides a robust implementation for handling matrices with various operations. Key features include:

- **Flexible Constructors**:
  - Create square matrices using `Matrix(size_t size)`.
  - Create rectangular matrices using `Matrix(size_t rows, size_t cols)`.

- **Element Access**:
  - Access matrix elements using the overloaded `operator()` for both constant and non-constant objects.

- **Matrix Operations**:
  - Addition: `Matrix operator+(const Matrix& other)` for adding two matrices.
  - Subtraction: `Matrix operator-(const Matrix& other)` for subtracting one matrix from another.
  - Multiplication: 
    - `Matrix operator*(const Matrix& other)` for matrix multiplication.
    - `Matrix operator*(double scalar)` for multiplying a matrix by a scalar.
  - Division: `Matrix operator/(double scalar)` for dividing a matrix by a scalar.

- **Advanced Matrix Functions**:
  - Transposition: `Matrix transpose() const` to obtain the transpose of a matrix.
  - Submatrix Extraction: `Matrix submatrix(size_t excludeRow, size_t excludeCol) const` to create a submatrix by excluding specified row and column.
  - Row Operations: `void swapRows(size_t row1, size_t row2)` to swap two rows in the matrix.
  
- **Determinants and Inverses**:
  - Calculate the determinant with `double determinant() const`.
  - Find the inverse of a matrix using `Matrix inverse() const`.

- **Rank and Power**:
  - Determine the rank of the matrix with `size_t rank() const`.
  - Raise the matrix to a power using `Matrix power(int exp) const`.

- **Random Filling and Display**:
  - Fill matrices with random values using `void fillRandom(int min = 0, int max = 100)`.
  - Display the matrix on screen with `void print()`.
