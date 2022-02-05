#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>
template <typename T>
class Matrix
{
public:
    class MatrixError
    {
        const char* message;
    public:
        MatrixError() : message("ERROR: matrices can not perform operation,enter a new matrix")
        {}
        const char* what() const
        {
            return message;
        }
    };
    Matrix(int, int);
    //constructor that takes parameters.
    //postcondition: calls the populate_matrix function to initialize the matrix.
    void PopulateMatrix();
    void print() const;
    T Evaluate(int, int, const Matrix&, int);
    Matrix operator+ (const Matrix&);
    Matrix operator- (const Matrix&);
    Matrix operator* (const Matrix&);
    const Matrix operator= (const Matrix&);
private:
    int row{ 0 };
    int column{ 0 };
    std::vector<std::vector<T>> any_vec;
};


template <typename T>
Matrix<T>::Matrix(int row, int column) : row(row), column(column)
{
    std::vector<std::vector<T>> temp_vec(row, std::vector<T>(column));
    for (int i{ 0 }; i < row; ++i)
    {
        for (int j{ 0 }; j < column; ++j)
        {
            temp_vec[i][j] = 0;
        }
    }
    any_vec = temp_vec;
}
template <typename T>
void Matrix<T>::PopulateMatrix()
{
    while (true)
    {
        try
        {
            std::cout << "\nEnter " << row << " rows of the matrix\n";
            for (auto i{ 0 }; i < row; ++i)
            {
                std::cout << "Row#" << i + 1 << " enter " << column << " values\n";
                for (auto j{ 0 }; j < column; ++j)
                    std::cin >> any_vec[i][j];
            }
            break;
        }
        catch (const std::exception& e)
        {
            std::cout << "\nERROR: an error occurred during input!\n" << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
template <typename T>
void Matrix<T>::print() const
{
    for (auto rows : any_vec)
    {
        std::cout << "{   ";
        for (T col : rows)
            std::cout << std::left << std::setw(5) << col;
        std::cout << "}";
        std::cout << '\n';
    }
}
template <typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix& other)
{
    if (row != other.row || column != other.column)
        throw MatrixError();
    Matrix tempMatrix(row, column);
    for (auto i{ 0 }; i < row; ++i)
    {
        for (int j{ 0 }; j < column; ++j)
            tempMatrix.any_vec[i][j] = any_vec[i][j] + other.any_vec[i][j];
    }
    return tempMatrix;
}
template <typename T>
Matrix<T> Matrix<T>::operator- (const Matrix& other)
{
    if (row != other.row || column != other.column)
        throw MatrixError();
    Matrix tempMatrix(row, column);
    for (auto i{ 0 }; i < row; ++i)
    {
        for (int j{ 0 }; j < column; ++j)
            tempMatrix.any_vec[i][j] = any_vec[i][j] - other.any_vec[i][j];
    }
    return tempMatrix;
}
template <typename T>
T Matrix<T>::Evaluate(int row, int col, const Matrix& other, int col2)
{
    int x{ 0 };
    T sum{ 0 };
    int row2{ col2 };
    while (x < col)
    {
        sum += any_vec[row][x] * other.any_vec[x][row2];
        ++x;
    }
    return sum;
}
template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix& other)
{
    if (column != other.row)
        throw MatrixError();
    Matrix tempMatrix(row, other.column);
    int i = 0;
    int j = 0;
    while (i < row)
    {
        while (true)
        {
            tempMatrix.any_vec[i][j] = Evaluate(i, column, other, j);
            ++j;
            if (j == other.column)
            {
                j = 0;
                break;
            }
        }
        ++i;
    }
    return tempMatrix;
}
template <typename T>
const Matrix<T> Matrix<T>::operator= (const Matrix& other)
{
    any_vec = other.any_vec;
    return *this;
}