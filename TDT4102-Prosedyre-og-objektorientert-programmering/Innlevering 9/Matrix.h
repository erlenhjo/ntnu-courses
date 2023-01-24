#pragma once
#include "iostream"
class Matrix{
    public:
        Matrix(int nrows,int nColoumns);
        ~Matrix();
        explicit Matrix(int nRows);
        double get(int row,int col) const;
        void set(int row,int col,double value);
        double* operator[](int i);
        int getRows() const;
        int getColoumns() const;
        friend std::ostream& operator<<(std::ostream& os,const Matrix& matrix);
        Matrix(const Matrix& rhs);
        Matrix& operator=(Matrix rhs);
        Matrix& operator+=(Matrix rhs);
        Matrix operator+(Matrix rhs);
    private:
        int rowNum;
        int colNum;
        double** M;
};
