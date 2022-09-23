#include "Matrix1D.hpp"
#include <math.h>
#include <iostream>

using namespace std;


typedef unsigned int CoordValue;

typedef struct {
    CoordValue row;
    CoordValue column;
} Coords;

template <class T>
class Matrix2D {
    public:
        CoordValue nRows;
        CoordValue nCols;
        T* matrix;

        Matrix2D(CoordValue nRows, CoordValue nCols);
        
        bool setElement(CoordValue row, CoordValue col, T value);
        T getElement(CoordValue row, CoordValue col);

        Matrix1D<T> getRowMatrix (CoordValue row);
        Matrix1D<T> getColumnMatrix (CoordValue column);

        Matrix2D<T> operator + (Matrix2D<T> matrix);
        Matrix2D<T> operator - (Matrix2D<T> matrix);
        Matrix2D operator * (Matrix2D<T> matrix);

    private:
        unsigned int getPos(CoordValue row, CoordValue col);
        Coords getCoords(int pos);
        unsigned int getLength();
        bool sameSize(Matrix2D<T> matrix);
};

/******************************************************************************************/

template <class T>
Matrix2D<T>::Matrix2D(CoordValue nRows, CoordValue nCols) {
    this->nRows = nRows;
    this->nCols = nCols;
    this->matrix = new T[this->getLength()];
}

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
bool Matrix2D<T>::setElement(CoordValue row, CoordValue col, T value) {
    if(row >= nRows || col >= nCols)
        return false;

    this->matrix[this->getPos(row, col)] = value;
    return true;
}

template <class T>
T Matrix2D<T>::getElement(CoordValue row, CoordValue col) {
    return this->matrix[this->getPos(row, col)];
}

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
unsigned int Matrix2D<T>::getPos(CoordValue row, CoordValue col) {
    return row * this->nCols + col;
}

template <class T>
Coords Matrix2D<T>::getCoords(int pos) {
    unsigned int row = round(pos / this->nCols);
    unsigned int column = pos - (row * this->nCols);
    Coords c;

    c.row = row;
    c.column = column;

    return c;
}

template <class T>
unsigned int Matrix2D<T>::getLength() {
    return this->nCols * this->nRows;
}

template <class T>
bool Matrix2D<T>::sameSize(Matrix2D<T> matrix) {
    return
        this->nRows == matrix.nRows &&
        this->nCols == matrix.nCols;
}