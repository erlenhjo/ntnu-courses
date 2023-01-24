#include "Matrix.h"
#include "assert.h"
#include "algorithm"

Matrix::Matrix(int nRows,int nColoumns)
    : rowNum{nRows},colNum{nColoumns}
    {
    assert(rowNum>0);
    assert(colNum>0);
    M=new double*[rowNum];
    for(int i{0};i<rowNum;++i){
        M[i]=new double[colNum]{};
    }
}
Matrix::Matrix(int nRows)
    : Matrix{nRows,nRows}
    {
        for(int i{0};i<rowNum;++i){
            M[i][i]=1;
        }
}
Matrix::Matrix(const Matrix& rhs)
    : Matrix{rhs.rowNum,rhs.colNum}
    {
        for(int i{0};i<rowNum;++i){
            for(int j{0};j<colNum;++j){
                M[i][j]=rhs.M[i][j];
            }
        }
}

Matrix::~Matrix(){
    for(int i{0}; i<rowNum;++i){
        delete[] M[i];
    }
    delete[] M;
    M=nullptr;
}

Matrix& Matrix::operator=(Matrix rhs){
    std::swap(rowNum,rhs.rowNum);
    std::swap(colNum, rhs.colNum);
    std::swap(M,rhs.M);
    return *this;
}

double Matrix::get(int row,int col) const{
    return M[row][col];
}
void Matrix::set(int row,int col,double value){
    M[row][col]=value;
}
double* Matrix::operator[](int i){
    return M[i];
}
int Matrix::getRows() const{
    return rowNum;
}
int Matrix::getColoumns() const{
    return colNum;
}
std::ostream& operator<<(std::ostream& os,const Matrix& matrix){    
    for(int i{0};i<matrix.rowNum;++i){
        for(int j{0};j<matrix.colNum;++j){
            std::cout<<matrix.M[i][j];
            if(j==matrix.colNum-1){
                std::cout<<"\n";
            }else{
                std::cout<<"\t";
            }
        }
    }
    return os;
}

Matrix& Matrix::operator+=(Matrix rhs){
    if(rowNum!=rhs.rowNum&&colNum!=rhs.colNum){
        std::cerr<<"Not valid matrix addition.";
    }
    for(int i{0};i<rowNum;++i){
        for(int j{0};j<colNum;++j){
            M[i][j]+=rhs.M[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator+(Matrix rhs){
    Matrix M{*this};
    return M+=rhs;
}