#include<stdio.h>
#include<stdlib.h>
#include"func.h"

// 卷积
void conv(NEWDATA *y,NEWDATA **input,float k,int type,int r){
  int i,j,m,n;
  int temp;
  // for input
  switch(type){
    // 此处针对不同的卷积进行优化
    case mean_type:
      i = r;{
        for(j=0;j<(COL);j++){
          // convolution: f*g*k
          temp = input[i][j]     + input[i][j+1]   + input[i][j+2]
               + input[i+1][j]   + input[i+1][j+1] + input[i+1][j+2]
               + input[i+2][j]   + input[i+2][j+1] + input[i+2][j+2];                    
          temp = temp * k / 9.0;
          y[j] += temp;
        }
      }
      break;

    case guassian_type:
      i = r;{
        for(j=0;j<(COL);j++){
          // convolution: f*g*k
          temp = input[i][j]     + input[i][j+1]*2   + input[i][j+2]
               + input[i+1][j]*2 + input[i+1][j+1]*4 + input[i+1][j+2]*2
               + input[i+2][j]   + input[i+2][j+1]*2 + input[i+2][j+2];          
          temp = (temp >> 4) * k;
          y[j] += temp;
        }  
      }        
      break;

    case highpass_type:
      i = r;{
        for(j=0;j<(COL);j++){
          // convolution: f*g*k
          temp = input[i][j]     + input[i][j+1]   + input[i][j+2]
               + input[i+1][j]                     + input[i+1][j+2]
               + input[i+2][j]   + input[i+2][j+1] + input[i+2][j+2];          
          // temp = input[i+1][j+1] * 9 - temp;
          temp = (input[i+1][j+1] << 3) + input[i+1][j+1] - temp;
          temp = temp * k ;
          y[j] += temp;
        }  
      }    
      break;

    case laplacian_type:
      i = r;{
        for(j=0;j<(COL);j++){
          // convolution: f*g*k
          temp = input[i][j]     + input[i][j+1]   + input[i][j+2]
               + input[i+1][j]                     + input[i+1][j+2]
               + input[i+2][j]   + input[i+2][j+1] + input[i+2][j+2];          
          // temp = temp - input[i+1][j+1]*8;
          temp = temp - (input[i+1][j+1] << 3);
          temp = temp * k ;
          y[j] += temp;
        }  
      }        
      break;

    default:      
      // for(i=0;i<(ROW);i++){
      //   for(j=0;j<(COL);j++){
      //     // convolution: f*g*k
      //     for(m=0;m<3;m++){
      //       for(n=0;n<3;n++){
      //         y[i][j] += input[i+m][j+n] * kernel[2-m][2-n] * k;
      //       }
      //     }
      //   }  
      // }      
      break;
  }
}

// 计算 y = k1 f_i * g_r + k2 f_i * g_g + k3 f_i * g_b
void calcul_y(NEWDATA *y, int type,NEWDATA ***input,float k1,float k2,float k3,FILE *out_y,int r){  
  clear_y(y);
  
  // k1,R    
  conv(y,input[0],k1,type,r);
  // k2,G    
  conv(y,input[1],k2,type,r); 
  // k3,B    
  conv(y,input[2],k3,type,r); 
  
  // check (< 0 & > 255)
  check_y(y);

  // write 直接将计算结果写入文件中
  fwrite(y,sizeof(NEWDATA),COL,out_y); 
}

// 从cmd读取小数
float read_float_number(char *a){
  int i;  
  float k = 0.0;  
  float v = 1.0;

  for(i = 2;i < strlen(a);i++){ 
    v = v * 0.1;      
    k = k + v * (int)(a[i] - '0');    
  }
  return k;
}