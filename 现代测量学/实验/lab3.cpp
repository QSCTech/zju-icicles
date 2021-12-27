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

void readFile(int &num, double *&pp_x, double *&pp_y, double *&pp_z, double *&gp_x, double *&gp_y, double *&gp_z) {
    ifstream data("./data3.txt");
    string tmp = "#";
    while (tmp[0] == '#') {
        getline(data, tmp);
    }
    sscanf(tmp.data(), "%d", &num);
    tmp = "#";
    pp_x = new double[num];
    pp_y = new double[num];
    pp_z = new double[num];
    gp_x = new double[num];
    gp_y = new double[num];
    gp_z = new double[num];
    while (tmp[0] == '#') {
        getline(data, tmp);
    }
    sscanf(tmp.data(), "%lf%lf%lf%lf%lf%lf", &pp_x[0], &pp_y[0], &pp_z[0], &gp_x[0], &gp_y[0], &gp_z[0]);
    for (int i = 1; i < num; i++) {
        getline(data, tmp);
        sscanf(tmp.data(), "%lf%lf%lf%lf%lf%lf", &pp_x[i], &pp_y[i], &pp_z[i], &gp_x[i], &gp_y[i], &gp_z[i]);
    }
}

void cal_R(Matrix &R, double p, double o, double k) {
    R[0][0] = cos(p) * cos(k) - sin(p) * sin(o) * sin(k);
    R[0][1] = -cos(p) * sin(k) - sin(p) * sin(o) * cos(k);
    R[0][2] = -sin(p) * cos(o);
    R[1][0] = cos(o) * sin(k);
    R[1][1] = cos(o) * cos(k);
    R[1][2] = -sin(o);
    R[2][0] = sin(p) * cos(k) + cos(p) * sin(o) * sin(k);
    R[2][1] = -sin(p) * sin(k) + cos(p) * sin(o) * cos(k);
    R[2][2] = cos(p) * cos(o);
}

int main() {
    //变量声明
    const double limit = 0.001;
    double *pp_x, *pp_y, *pp_z, *gp_x, *gp_y, *gp_z;
    int num;
    double p = 0, o = 0, k = 0, x = 0, y = 0, z = 0, l = 0;

    //读取文件
    readFile(num, pp_x, pp_y, pp_z, gp_x, gp_y, gp_z);

    Matrix R(3, 3), A(num * 3, 7), L(num * 3, 1), X(7, 1);
    while (true) {
        //遍历所有点
        for (int i = 0; i < num; i++) {
            //计算R
            cal_R(R, p, o, k);
            //计算L
            L[3 * i + 0][0] = gp_x[i] - l * (R[0][0] * pp_x[i] + R[0][1] * pp_y[i] + R[0][2] * pp_z[i]) - x;
            L[3 * i + 1][0] = gp_y[i] - l * (R[1][0] * pp_x[i] + R[1][1] * pp_y[i] + R[1][2] * pp_z[i]) - y;
            L[3 * i + 2][0] = gp_z[i] - l * (R[2][0] * pp_x[i] + R[2][1] * pp_y[i] + R[2][2] * pp_z[i]) - z;
            //计算A
            A[3 * i + 0][0] = 1;
            A[3 * i + 0][3] = pp_x[i];
            A[3 * i + 0][4] = -pp_z[i];
            A[3 * i + 0][6] = -pp_y[i];
            A[3 * i + 1][1] = 1;
            A[3 * i + 1][3] = pp_y[i];
            A[3 * i + 1][5] = -pp_z[i];
            A[3 * i + 1][6] = pp_x[i];
            A[3 * i + 2][2] = 1;
            A[3 * i + 2][3] = pp_z[i];
            A[3 * i + 2][4] = pp_x[i];
            A[3 * i + 2][5] = pp_y[i];
        }
        //获得X
        X = (A.tsp() * A).inv() * A.tsp() * L;
        //修正参数
        x += X[0][0];
        y += X[1][0];
        z += X[2][0];
        l += X[3][0];
        p += X[4][0];
        o += X[5][0];
        k += X[6][0];
        //判断限界
        bool isLimit = true;
        for (int i = 0; i < 7; i++) {
            if (abs(X[i][0]) > 0.001) isLimit = false;
        }
        if (isLimit) break;
    }
    fprintf(stdout, "%.3lf %.3lf %.3lf %.6lf %.6lf %.6lf %.6lf\n", x, y, z, l, p, o, k);
    return 0;
}
