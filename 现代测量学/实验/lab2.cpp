#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

class Matrix {
private:
    int cols, rows;
    double **p;
public:
    Matrix(int, int);//声明一个rows行cols列 初始值为0的矩阵

    //矩阵操作
    Matrix tsp();//转置
    Matrix adjt();//伴随
    Matrix minor(int r, int c);//余子式
    double value();//矩阵的值
    Matrix inv();//逆

    //矩阵运算
    template<size_t r, size_t c>
    Matrix operator=(double(&pp)[r][c]);//二维数组赋值
    Matrix operator*(const Matrix &m) const;//矩阵乘法
    double *&operator[](int index);

    Matrix operator/(double d);//矩阵除法
    friend ostream &operator<<(ostream &, Matrix &);//输出矩阵
    friend istream &operator>>(istream &, Matrix &);//按行输入
};

Matrix::Matrix(int rows_num, int cols_num) {
    cols = cols_num;
    rows = rows_num;
    p = new double *[rows];//申请rows个指针，存放cols个元素
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

double Matrix::value() {
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

ostream &operator<<(ostream &out, Matrix &m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            out << m.p[i][j] << ' ';
        }
        out << endl;
    }
    return out;
}

Matrix Matrix::operator*(const Matrix &m) const {
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

Matrix Matrix::operator/(double d) {
    Matrix tmp(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tmp.p[i][j] = p[i][j] / d;
        }
    }
    return tmp;
}

template<size_t r, size_t c>
Matrix Matrix::operator=(double(&pp)[r][c]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            this->p[i][j] = pp[i][j];
        }
    }
    return *this;
}

double *&Matrix::operator[](int index) {
    return p[index];
}

istream &operator>>(istream &in, Matrix &m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            in >> m.p[i][j];
        }
    }
    return in;
}

void readFile(double &f, int &num, double *&x_left, double *&y_left, double *&x_right, double *&y_right) {
    ifstream data("./data2.txt");
    string tmp = "#";
    while (tmp[0] == '#') {
        getline(data, tmp);
    }
    sscanf(tmp.data(), "%lf", &f);
    f /= 1000.0;
    tmp = "#";
    while (tmp[0] == '#') {
        getline(data, tmp);
    }
    sscanf(tmp.data(), "%d", &num);
    tmp = "#";
    x_left = new double[num];
    y_left = new double[num];
    x_right = new double[num];
    y_right = new double[num];
    while (tmp[0] == '#') {
        getline(data, tmp);
    }
    sscanf(tmp.data(), "%lf%lf%lf%lf", &x_left[0], &y_left[0], &x_right[0], &y_right[0]);
    for (int i = 1; i < num; i++) {
        getline(data, tmp);
        sscanf(tmp.data(), "%lf%lf%lf%lf", &x_left[i], &y_left[i], &x_right[i], &y_right[i]);
    }
    for (int i = 0; i < num; i++) {
        x_left[i] /= 1000.0;
        x_right[i] /= 1000.0;
        y_left[i] /= 1000.0;
        y_right[i] /= 1000.0;
    }
}

void cal_R(Matrix &R, double(&eo_angles)[3]) {
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

void cal_AP(Matrix &R, double x, double y, double f, double(&coord)[3]) {
    for (int i = 0; i < 3; i++) {
        coord[i] = R[i][0] * x + R[i][1] * y - R[i][2] * f;
    }
}

int main() {
    const double limit = 0.00003;
    double a_coordl[3] = {0}, a_coordr[3] = {0};//空间辅助坐标系
    double r_angles[3] = {0}, r_coord[3] = {5.185 / 1000.0, 0, 0}, u = 0, v = 0;//相对定向元素
    double n1, n2;//投影系数
    double *x_left, *x_right, *y_left, *y_right;
    double f;
    int num;

    readFile(f, num, x_left, y_left, x_right, y_right);
    //初始化矩阵变量
    Matrix R(3, 3);
    Matrix A(num, 5), X(5, 1), L(num, 1);
    while (true) {
        //计算右片方向余弦值
        cal_R(R, r_angles);
        for (int i = 0; i < num; i++) {//对每一个像点
            //计算空间辅助坐标系
            a_coordl[0] = x_left[i];
            a_coordl[1] = y_left[i];
            a_coordl[2] = -f;
            cal_AP(R, x_right[i], y_right[i], f, a_coordr);
            //计算by、bz以及N1、N2
            r_coord[1] = u * r_coord[0];
            r_coord[2] = v * r_coord[0];
            n1 = (r_coord[0] * a_coordr[2] - r_coord[2] * a_coordr[0]) /
                 (a_coordl[0] * a_coordr[2] - a_coordl[2] * a_coordr[0]);
            n2 = (r_coord[0] * a_coordl[2] - r_coord[2] * a_coordl[0]) /
                 (a_coordl[0] * a_coordr[2] - a_coordl[2] * a_coordr[0]);

            //计算误差方程式系数
            A[i][0] = -(a_coordr[0] * a_coordr[1] / a_coordr[2]) * n2;
            A[i][1] = -(a_coordr[2] + pow(a_coordr[1], 2) / a_coordr[2]) * n2;
            A[i][2] = a_coordr[0] * n2;
            A[i][3] = r_coord[0];
            A[i][4] = -(a_coordr[1] / a_coordr[2] * r_coord[0]);
            L[i][0] = n1 * a_coordl[1] - n2 * a_coordr[1] - r_coord[1];
        }
        X = (A.tsp() * A)
                    .inv() * A.tsp()
            * L;
        //修正相对定向元素
        r_angles[0] += X[0][0];
        r_angles[1] += X[1][0];
        r_angles[2] += X[2][0];
        u += X[3][0];
        v += X[4][0];
        //判断改正数是否满足限制
        if (fabs(X[0][0]) < limit && fabs(X[1][0]) < limit && fabs(X[2][0]) < limit && fabs(X[3][0]) < limit &&
            fabs(X[4][0]) < limit)
            break;
    }
    fprintf(stdout, "%.6lf %.6lf %.6lf %.6lf %.6lf \n", r_angles[0], r_angles[1], r_angles[2], u, v);
    delete[] x_left;
    delete[] x_right;
    delete[] y_left;
    delete[] y_right;
    return 0;
}
