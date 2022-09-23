#include "Matrix2D.hpp"
#include <iostream>

using namespace std;

int main() {
    Matrix2D<int> matrix(2, 3);
    Matrix2D<int> matrix2(3, 2);
    matrix.setElement(0, 0, 1);
    matrix.setElement(0, 1, 2);
    matrix.setElement(0, 2, 3);
    matrix.setElement(1, 0, 4);
    matrix.setElement(1, 1, 5);
    matrix.setElement(1, 2, 6);

    matrix2.setElement(0, 0, 7);
    matrix2.setElement(0, 1, 8);
    matrix2.setElement(1, 0, 9);
    matrix2.setElement(1, 1, 10);
    matrix2.setElement(2, 0, 11);
    matrix2.setElement(2, 1, 12);

    Matrix2D<int> matrix3 = matrix * matrix2;

    cout << matrix3.getElement(0,0) <<endl;
    cout << matrix3.getElement(0,1) <<endl;
    cout << matrix3.getElement(1,0) <<endl;
    cout << matrix3.getElement(1,1) <<endl;
    return 0;
}