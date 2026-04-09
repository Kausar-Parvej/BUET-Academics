
#ifndef MATRIX_CPP
#define MATRIX_CPP

#include <iostream>
#include <vector>

using namespace std;

class Matrix {

public:
    vector< vector<double> > data;

    Matrix(int n_rows, int n_cols);
    Matrix(vector<vector<double>> data);
    //~Matrix();

    void identity();
    Matrix operator*(const Matrix &mat2);
    Matrix operator*=(const Matrix &mat2);


};


Matrix::Matrix(int n_rows, int n_cols) {
    data = vector<vector<double>>(n_rows, vector<double>(n_cols, 0.0));
}

Matrix::Matrix(vector<vector<double>> data) {
    this->data = data;
}



void Matrix :: identity() {
    for(int i=0; i<data.size(); i++){
        for(int j=0; j<data[i].size(); j++){
            if(i == j) data[i][j] = 1.0;
            else data[i][j] = 0.0;
        }
    }
}

Matrix Matrix :: operator*(const Matrix &mat2){
    if(this->data[0].size() != mat2.data.size()){
        printf("Matrix multiplication error: Incompatible matrix dimensions\n");
        exit(1);
    }

    int row_num = this->data.size();
    int col_num = mat2.data[0].size();

    Matrix result(row_num, col_num);
    for(int i=0; i<row_num; i++){
        for(int j=0; j<col_num; j++){
            for(int k=0; k<this->data[0].size(); k++){
                result.data[i][j] += this->data[i][k] * mat2.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix :: operator*=(const Matrix &mat2){
    (*this) = (*this) * mat2;
    return *this;
}



ostream &operator<<(ostream &os, const Matrix &m) {
    for (const auto &row : m.data) {
        for (const auto &a : row) {
            os << a << " ";
        }
        os << "\n";
    }
    return os;
}



#endif // MATRIX_CPP