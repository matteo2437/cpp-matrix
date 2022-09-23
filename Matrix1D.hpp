typedef unsigned int CoordValue;

template <class T>
class Matrix1D {
    public:
        CoordValue length;
        T* matrix;

        Matrix1D(CoordValue length);
        
        bool setElement(CoordValue pos, T value);
        T getElement(CoordValue pos);

        Matrix1D<T> operator + (Matrix1D<T> matrix);
        Matrix1D<T> operator - (Matrix1D<T> matrix);
        T operator * (Matrix1D<T> matrix);

    private:
        bool sameSize(Matrix1D<T> matrix);
};

/******************************************************************************************/

template <class T>
Matrix1D<T>::Matrix1D(CoordValue length) {
    this->length = length;
    this->matrix = new T[length];
}

template <class T>
bool Matrix1D<T>::setElement(CoordValue pos, T value) {
    if(pos >= this->length)
        return false;

    this->matrix[pos] = value;
    return true;
}

template <class T>
T Matrix1D<T>::getElement(CoordValue pos) {
    return this->matrix[pos];
}

template <class T>
Matrix1D<T> Matrix1D<T>::operator + (Matrix1D<T> matrix) {
    if(!this->sameSize(matrix)) return *this;

    Matrix1D<T> temp(this->length);

    for(int pos = 0; pos < this->length; pos++) {
        temp.matrix[pos] = this->matrix[pos] + matrix.matrix[pos]; 
    }

    return temp;
}

template <class T>
Matrix1D<T> Matrix1D<T>::operator - (Matrix1D<T> matrix) {
    if(!this->sameSize(matrix)) return *this;

    Matrix1D<T> temp(this->length);

    for(int pos = 0; pos < this->length; pos++) {
        temp.matrix[pos] = this->matrix[pos] - matrix.matrix[pos]; 
    }
    
    return temp;
}

template <class T>
T Matrix1D<T>::operator * (Matrix1D<T> matrix) {
    T value = 0;
    for(int pos = 0; pos < this->length; pos++) {
        value += this->matrix[pos] * matrix.matrix[pos]; 
    }

    return value;
}

template <class T>
bool Matrix1D<T>::sameSize(Matrix1D<T> matrix) {
    return this->length == matrix.length;
}