// 图像大小
#define ROW 1024// h
#define COL 2048// w

// 四种卷积核
#define mean_type 0
#define guassian_type 1
#define highpass_type 2
#define laplacian_type 3

// 16-bit
#define NEWDATA short

// 宏定义函数
#define clear_y(y) {int j;for(j=0;j<COL;j++) y[j] = 0;}
#define check_y(y) {int j;for(j=0;j<COL;j++) {if(y[j]<0) y[j] = 0; if(y[j]>255) y[j] = 255;y[j] = (NEWDATA)(y[j]);} }

// 读取k1,k2,k3
float read_float_number(char *a);

// 卷积有关的函数
void conv(NEWDATA *y,NEWDATA **input,float k,int type,int r);
void calcul_y(NEWDATA *y, int type,NEWDATA ***input,float k1,float k2,float k3,FILE *out_y,int r);
