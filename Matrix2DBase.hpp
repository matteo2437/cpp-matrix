#include <math.h>
#include <iostream>

using namespace std;

typedef unsigned int UInt;

typedef struct {
    UInt row;
    UInt column;
} Coords;

template <class T>
class Matrix2DBase {
    public:
    UInt nRows;
    UInt nCols;
    T* matrix;

    Matrix2DBase(UInt nRows, UInt nCols);
    
    bool setElement(UInt row, UInt col, T value);
    T getElement(UInt row, UInt col);

    virtual Matrix2DBase<T> operator + (Matrix2DBase<T> matrix);
    virtual Matrix2DBase<T> operator - (Matrix2DBase<T> matrix);
    virtual Matrix2DBase<T> operator * (Matrix2DBase<T> matrix);

    protected:
    UInt getPos(UInt row, UInt col);
    UInt getLength();
    Coords getCoords(int pos);
};

/******************************************************************************************/

template <class T>
Matrix2DBase<T>::Matrix2DBase(UInt nRows, UInt nCols) {
    this->nRows = nRows;
    this->nCols = nCols;
    this->matrix = new T[this->getLength()];
}

template <class T>
bool Matrix2DBase<T>::setElement(UInt row, UInt col, T value) {
    if(row >= nRows || col >= nCols)
        return false;

    this->matrix[this->getPos(row, col)] = value;
    return true;
}

template <class T>
T Matrix2DBase<T>::getElement(UInt row, UInt col) {
    return this->matrix[this->getPos(row, col)];
}

template <class T>
UInt Matrix2DBase<T>::getPos(UInt row, UInt col) {
    return row * this->nCols + col;
}

template <class T>
Coords Matrix2DBase<T>::getCoords(int pos) {
    UInt row = round(pos / this->nCols);
    UInt column = pos - (row * this->nCols);
    Coords c;

    c.row = row;
    c.column = column;

    return c;
}

template <class T>
UInt Matrix2DBase<T>::getLength() {
    return this->nCols * this->nRows;
}