#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <string>
using namespace std;

class Matrix {
private:
    int cols, rows;
    double** p;
public:
    Matrix(int, int);//声明一个rows行cols列 初始值为0的矩阵
    
    //矩阵操作
    Matrix tsp();//转置
    Matrix adjt();//伴随
    Matrix minor(int r, int c);//余子式
    double value();//矩阵的值
    Matrix inv();//逆

    //矩阵运算
    template <size_t r, size_t c>
    Matrix operator= (double(&pp)[r][c]);//二维数组赋值
    Matrix operator* (const Matrix& m)const;//矩阵乘法
    double*& operator[] (int index);
    Matrix operator/ (double d);//矩阵除法
    friend ostream& operator<< (ostream&, Matrix&);//输出矩阵
    friend istream& operator>> (istream&, Matrix&);//按行输入
};

Matrix::Matrix(int rows_num, int cols_num) {
    cols = cols_num;
    rows = rows_num;
    p = new double* [rows];//申请rows个指针，存放cols个元素
    for (int i = 0; i < rows; i++) {
        p[i] = new double[cols];
        for (int j = 0; j < cols; j++) p[i][j] = 0;
    }
}

Matrix Matrix::tsp() {
    Matrix T(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            T.p[j][i] = p[i][j];
        }
    }
    return T;
}

Matrix Matrix::minor(int r, int c) {
    Matrix tmp(rows - 1, cols - 1);
    for (int i = 0, tmpi = 0; i < rows; i++) {
        if (i == r) continue;
        for (int j = 0, tmpj = 0; j < cols; j++) {
            if (j == c) continue;
            else {
                tmp.p[tmpi][tmpj] = p[i][j];
                tmpj++;
            }
        }
        tmpi++;
    }
    return tmp;
}

double Matrix::value(){
    double value = 0;
    if (rows == 1) return p[0][0];
    if (rows == 2) return p[0][0] * p[1][1] - p[0][1] * p[1][0];
    for (int i = 0; i < rows; i++) {
        if (i % 2 == 0) value += minor(i, 0).value() * p[i][0];
        else value += minor(i, 0).value() * p[i][0] * (-1);
    }
    return value;
}

Matrix Matrix::adjt() {
    Matrix tmp(rows, cols);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            if ((i + j) % 2 == 0) tmp.p[i][j] = minor(j, i).value();
            else tmp.p[i][j] = minor(j, i).value() * (-1);
        }
    }
    return tmp;
}

Matrix Matrix::inv() {
    Matrix tmp(rows, cols);
    tmp = adjt() / value();
    return tmp;
}

ostream& operator<< (ostream& out, Matrix& m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            out << m.p[i][j] << ' ';
        }
        out << endl;
    }
    return out;
}

Matrix Matrix::operator* (const Matrix& m)const {
    Matrix result(rows, m.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            for (int k = 0; k < cols; k++) {
                result.p[i][j] += p[i][k] * m.p[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator/ (double d) {
    Matrix tmp(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tmp.p[i][j] = p[i][j] / d;
        }
    }
    return tmp;
}

template <size_t r, size_t c>
Matrix Matrix::operator= (double(&pp)[r][c]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            this->p[i][j] = pp[i][j];
        }
    }
    return *this;
}

double*& Matrix::operator[] (int index) {
    return p[index];
}

istream& operator>>(istream& in, Matrix& m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            in >> m.p[i][j];
        }
    }
    return in;
}

void readFile(double& f, double& x0, double& y0, int& m, int& num, double**& pp, double**& gp) {
    ifstream data("./data1.txt");
    string tmp = "#";
    while (tmp[0] == '#') {
        getline(data, tmp);
    }
    sscanf(tmp.data(), "%lf%lf%lf", &x0, &y0, &f);
    f /= 1000.0;
    tmp = "#";
    while (tmp[0] == '#') {
        getline(data, tmp);
    }
    sscanf(tmp.data(), "%d", &m);
    tmp = "#";
    while (tmp[0] == '#') {
        getline(data, tmp);
    }
    sscanf(tmp.data(), "%d", &num);
    tmp = "#";
    pp = new double* [num];
    for (int i = 0; i < num; i++) pp[i] = new double[2];
    gp = new double* [num];
    for (int i = 0; i < num; i++) gp[i] = new double[3];
    while (tmp[0] == '#') {
        getline(data, tmp);
    }
    sscanf(tmp.data(), "%lf%lf%lf%lf%lf", &pp[0][0], &pp[0][1], &gp[0][0], &gp[0][1], &gp[0][2]);
    for (int i = 1; i < num; i++) {
        getline(data, tmp);
        sscanf(tmp.data(), "%lf%lf%lf%lf%lf", &pp[i][0], &pp[i][1], &gp[i][0], &gp[i][1], &gp[i][2]);
    }
    for (int i = 0; i < num; i++) {
        pp[i][0] /= 1000.0;
        pp[i][1] /= 1000.0;
    }
}

void init(double(&eo_coords)[3], double& f, int& m, int& num, double**& gp, double**&ap) {
    ap = new double* [num];
    for (int i = 0; i < num; i++) {
        ap[i] = new double[2];
        eo_coords[0] += gp[i][0];
        eo_coords[1] += gp[i][1];
        eo_coords[2] += gp[i][2];
    }
    eo_coords[0] /= num;
    eo_coords[1] /= num;
    eo_coords[2] = f * m;
}

void cal_R(Matrix& R, double(&eo_angles)[3]) {
    R[0][0] = cos(eo_angles[0]) * cos(eo_angles[2]) - sin(eo_angles[0]) * sin(eo_angles[1]) * sin(eo_angles[2]);
    R[0][1] = -cos(eo_angles[0]) * sin(eo_angles[2]) - sin(eo_angles[0]) * sin(eo_angles[1]) * cos(eo_angles[2]);
    R[0][2] = -sin(eo_angles[0]) * cos(eo_angles[1]);
    R[1][0] = cos(eo_angles[1]) * sin(eo_angles[2]);
    R[1][1] = cos(eo_angles[1]) * cos(eo_angles[2]);
    R[1][2] = -sin(eo_angles[1]);
    R[2][0] = sin(eo_angles[0]) * cos(eo_angles[2]) + cos(eo_angles[0]) * sin(eo_angles[1]) * sin(eo_angles[2]);
    R[2][1] = -sin(eo_angles[0]) * sin(eo_angles[2]) + cos(eo_angles[0]) * sin(eo_angles[1]) * cos(eo_angles[2]);
    R[2][2] = cos(eo_angles[0]) * cos(eo_angles[1]);
}

void apxm(double(&eo_coords)[3], int& num, double &f, double**& gp, double**& ap, Matrix& R) {
    for (int i = 0; i < num; i++) {
        ap[i][0] = -f * (R[0][0] * (gp[i][0] - eo_coords[0]) + R[1][0] * (gp[i][1] - eo_coords[1]) + R[2][0] * (gp[i][2] - eo_coords[2])) / (R[0][2] * (gp[i][0] - eo_coords[0]) + R[1][2] * (gp[i][1] - eo_coords[1]) + R[2][2] * (gp[i][2] - eo_coords[2]));
        ap[i][1] = -f * (R[0][1] * (gp[i][0] - eo_coords[0]) + R[1][1] * (gp[i][1] - eo_coords[1]) + R[2][1] * (gp[i][2] - eo_coords[2])) / (R[0][2] * (gp[i][0] - eo_coords[0]) + R[1][2] * (gp[i][1] - eo_coords[1]) + R[2][2] * (gp[i][2] - eo_coords[2]));
    }
}

void cal_A(Matrix& A, Matrix& R, double**& pp, double**& gp, double& f, double(&eo_angles)[3], double(&eo_coords)[3], int& num) {
    for (int i = 0; i < num; i++) {
        double Z = R[0][2] * (gp[i][0] - eo_coords[0]) + R[1][2] * (gp[i][1] - eo_coords[1]) + R[2][2] * (gp[i][2] - eo_coords[2]);
        A[i * 2][0] = (R[0][0] * f + R[0][2] * pp[i][0]) / Z;//a11
        A[i * 2][1] = (R[1][0] * f + R[1][2] * pp[i][0]) / Z;//a12
        A[i * 2][2] = (R[2][0] * f + R[2][2] * pp[i][0]) / Z;//a13
        A[i * 2][3] = pp[i][1] * sin(eo_angles[1]) - (pp[i][0] * (pp[i][0] * cos(eo_angles[2])
            - pp[i][1] * sin(eo_angles[2])) / f + f * cos(eo_angles[2])) * cos(eo_angles[1]);//a14
        A[i * 2][4] = -f * sin(eo_angles[2]) - pp[i][0] * (pp[i][0] * sin(eo_angles[2])
            + pp[i][1] * cos(eo_angles[2])) / f;//a15
        A[i * 2][5] = pp[i][1];//a16
        A[i * 2 + 1][0] = (R[0][1] * f + R[0][2] * pp[i][1]) / Z;//a21
        A[i * 2 + 1][1] = (R[1][1] * f + R[1][2] * pp[i][1]) / Z;//a22
        A[i * 2 + 1][2] = (R[2][1] * f + R[2][2] * pp[i][1]) / Z;//a23
        A[i * 2 + 1][3] = -pp[i][0] * sin(eo_angles[1]) - (pp[i][1] * (pp[i][0] * cos(eo_angles[2])
            - pp[i][1] * sin(eo_angles[2])) / f - f * sin(eo_angles[2])) * cos(eo_angles[1]);//a24
        A[i * 2 + 1][4] = -f * cos(eo_angles[2]) - (pp[i][1] * (pp[i][0] * sin(eo_angles[2])
            + pp[i][1] * cos(eo_angles[2]))) / f;//a25
        A[i * 2 + 1][5] = -pp[i][0];//a26
    }
}

void cal_L(Matrix& L, double**& pp, double**& ap, int& num) {
    for (int i = 0; i < num; i++) {
        L[i * 2][0] = pp[i][0] - ap[i][0];
        L[i * 2 + 1][0] = pp[i][1] - ap[i][1];
    }
}

void modify(double(&eo_coords)[3], double(&eo_angles)[3], Matrix& X) {
    eo_coords[0] += X[0][0];
    eo_coords[1] += X[1][0];
    eo_coords[2] += X[2][0];
    eo_angles[0] += X[3][0];
    eo_angles[1] += X[4][0];
    eo_angles[2] += X[5][0];
}

int main()
{
    //参数定义
    int m, num = 0;//num:控制点对数
    double x0, y0, f;
    double eo_coords[3] = { 0 }, eo_angles[3] = { 0 };
    double** pp = NULL, ** gp = NULL, **ap= NULL;//ap:近似值
    readFile(f, x0, y0, m, num, pp, gp);
    Matrix A(2 * num, 6);//误差方程系数
    Matrix R(3, 3);
    Matrix L(2 * num, 1);
    Matrix X(6, 1);//修改值
    //估算摄站初始位置和姿态
    init(eo_coords, f, m, num, gp, ap);
    do {
        //计算R
        cal_R(R, eo_angles);
        //计算控制点估计值
        apxm(eo_coords, num, f, gp, ap, R);
        //误差方程式系数
        cal_A(A, R, pp, gp, f, eo_angles, eo_coords, num);
        //l计算
        cal_L(L, pp, ap, num);
        //计算修改值X
        X = (A.tsp() * A).inv() * A.tsp() * L;
        //修正外方位元素
        modify(eo_coords, eo_angles, X);
        if (fabs(X[3][0]) < 0.01 && fabs(X[4][0]) < 0.01 && fabs(X[5][0]) < 0.01) break;
    }     while (true);
    fprintf(stdout, "%.2lf %.2lf %.2lf %.6lf %.6lf %.6lf\n", eo_coords[0], eo_coords[1], eo_coords[2], eo_angles[0], eo_angles[1], eo_angles[2]);
    return 0;
}