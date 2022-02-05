#include "Matrix.h"
#include <limits>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std::chrono;
void showMatrixMenu(int* operation)
{
    while (true)
    {
        std::cout << "*******program to handle matrix operations**********\n";
        std::cout << "1> matrix addition\n";
        std::cout << "2> matrix subtraction\n";
        std::cout << "3> matrix multiplication\n";
        try
        {
            std::cin >> *operation;
            if (*operation > 0 && *operation < 4)
                break;
        }
        catch (const std::exception&)
        {
            std::cout << "\nERROR: input error!\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
void getMatrixDimension(int* row, int* col)
{
    while (true)
    {
        try
        {
            std::cout << "\nrow:";
            std::cin >> *row;
            std::cout << "\ncolumn:";
            std::cin >> *col;
            break;
        }
        catch (const std::exception&)
        {
            std::cout << "\nERROR: input error!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
void initialize(Matrix<int>& matrixA, Matrix<int>& matrixB)
{
    matrixA.PopulateMatrix();
    matrixB.PopulateMatrix();
}
int main()
{
    std::cin.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    int operation{ 0 };
    while (true)
    {
        showMatrixMenu(&operation);
        if (operation == 1)
        {
            std::cout << "To add two matrices,they must be of equal size!\n";
            std::cout << "\nEnter the number of rows and columns of the matrix:\n";
            auto row{ 0 }, col{ 0 };
            getMatrixDimension(&row, &col);
            Matrix<int> matrixA(row, col);
            Matrix<int> matrixB(row, col);
            std::cout << "\n********INITIALIZE THE MATRICES*********\n";
            initialize(matrixA, matrixB);
            std::cout << "\n********INITIALIZATION COMPLETE*********\n";
            matrixA.print();
            std::cout << "       + \n";
            matrixB.print();
            std::cout << "       = \n";
            Matrix<int> temp(row, col);
            temp = matrixA + matrixB;
            temp.print();
        }
        else if (operation == 2)
        {
            std::cout << "To subtract  two matrices,they must be of equal size!\n";
            std::cout << "\nEnter the number of rows and columns of the matrix:\n";
            auto row{ 0 }, col{ 0 };
            getMatrixDimension(&row, &col);
            Matrix<int> matrixA(row, col);
            Matrix<int> matrixB(row, col);
            std::cout << "\n********INITIALIZE THE MATRICES*********\n";
            initialize(matrixA, matrixB);
            std::cout << "********INITIALIZATION COMPLETE*********\n";
            matrixA.print();
            std::cout << "       - \n";
            matrixB.print();
            std::cout << "       = \n";
            Matrix<int> temp(row, col);
            temp = matrixA - matrixB;
            temp.print();
        }
        else
        {
            std::cout << "To multiply two matrices,they must be of type (m,n) * (n,k) = (m,k)!\n";
            std::cout << "\nEnter the number of rows and columns of the matrix:\n";
            auto row1{ 0 }, row2{ 0 }, col1{ 0 }, col2{ 0 };
            std::cout << "\n****MATRIX 1******\n";
            getMatrixDimension(&row1, &col1);
            std::cout << "\n****MATRIX 2******\n";
            getMatrixDimension(&row2, &col2);
            Matrix<int> matrixA(row1, col1);
            Matrix<int> matrixB(row2, col2);
            std::cout << "\n********INITIALIZE THE MATRICES*********\n";
            initialize(matrixA, matrixB);
            std::cout << "********INITIALIZATION COMPLETE*********\n";
            matrixA.print();
            std::cout << "       * \n";
            matrixB.print();
            std::cout << "       = \n";
            Matrix<int> temp(row1, col2);
            temp = matrixA * matrixB;
            temp.print();
        }
        std::cout << "\nDo you want to continue\ny> yes\n\npress any key to exit\n";
        auto choice{ ' ' };
        std::cin >> choice;
        if (choice != 'y')
            break;
    }
    std::cout << "Matrix calculator will exit in 3 seconds\n";
    for (auto counter{ 3 }; counter >= 0; --counter)
    {
        std::this_thread::sleep_for(1s);
        for (auto i{ 0 }; i < 30; ++i)
            std::cout << '\n';
        std::cout << "                                                                   " << counter;
    }
}
