#include "Matrix2DBase.hpp"
#include "Matrix1D.hpp"
#include <math.h>
#include <iostream>

using namespace std;

template <class T>
class Matrix2D: public Matrix2DBase<T> {
    public:
    Matrix2D(UInt nRows, UInt nCols);

    Matrix1D<T> getRowMatrix (CoordValue row);
    Matrix1D<T> getColumnMatrix (CoordValue column);

    Matrix2D<T> operator + (Matrix2D<T> matrix);
    Matrix2D<T> operator - (Matrix2D<T> matrix);
    Matrix2D operator * (Matrix2D<T> matrix);

    private:
    bool sameSize(Matrix2D<T> matrix);
};

/******************************************************************************************/

template <class T>
Matrix1D<T> Matrix2D<T>::getRowMatrix(CoordValue row)  {
    Matrix1D<T> newMatrix(this->nCols);
    
    for(int c = 0; c < this->nCols; c++) {
        T value = this->getElement(row, c);
        newMatrix.setElement(c, value);
    }

    return newMatrix;
}

template <class T>
Matrix1D<T> Matrix2D<T>::getColumnMatrix(CoordValue column)  {
    Matrix1D<T> newMatrix(this->nRows);
    
    for(int r = 0; r < this->nRows; r++) {
        T value = this->getElement(r, column);
        newMatrix.setElement(r, value);
    }

    return newMatrix;
}

template <class T>
Matrix2D<T>::Matrix2D(UInt nRows, UInt nCols) : 
    Matrix2DBase<T>(nRows, nCols) { }

template <class T>
Matrix2D<T> Matrix2D<T>::operator + (Matrix2D<T> matrix) {
    if(!this->sameSize(matrix)) return *this;

    Matrix2D<T> temp(this->nRows, this->nCols);

    for(int pos = 0; pos < this->getLength(); pos++) {
        temp.matrix[pos] = this->matrix[pos] + matrix.matrix[pos]; 
    }

    return temp;
}

template <class T>
Matrix2D<T> Matrix2D<T>::operator - (Matrix2D<T> matrix) {
    if(!this->sameSize(matrix)) return *this;

    Matrix2D<T> temp(this->nRows, this->nCols);

    for(int pos = 0; pos < this->getLength(); pos++) {
        temp.matrix[pos] = this->matrix[pos] - matrix.matrix[pos]; 
    }
    
    return temp;
}

template <class T>
Matrix2D<T> Matrix2D<T>::operator * (Matrix2D<T> matrix) {
    bool canMultiplicate = 
        this->nRows == matrix.nCols &&
        this->nCols == matrix.nRows;

    if(!canMultiplicate) return *this;

    Matrix2D<T> temp(this->nRows, matrix.nCols);
    for(int pos = 0; pos < temp.getLength(); pos++) {
        Coords coords = temp.getCoords(pos);

        temp.matrix[pos] = 
            this->getRowMatrix(coords.row) * 
            matrix.getColumnMatrix(coords.column);
    }

    return temp;
}

template <class T>
bool Matrix2D<T>::sameSize(Matrix2D<T> matrix) {
    return
        this->nRows == matrix.nRows &&
        this->nCols == matrix.nCols;
}