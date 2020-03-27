#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"func.h"
#include"func.c"

int main(int argc, char *argv[]){
  if(argc != 6)
  {
    fprintf(stderr, "Usage: ./conv in_bin_file out_bin_file k1 k2 k3\n");
    return 1;
  }


  // @Part.1 weight
  // 读入k1, k2, k3的值
  fprintf(stderr,"------------------Part.1 Weight------------------\n");   
  float k1 = read_float_number(argv[3]); 
  float k2 = read_float_number(argv[4]); 
  float k3 = read_float_number(argv[5]); 
  fprintf(stderr,"k1 = %.5f, k2 = %.5f, k3 = %.5f\n",k1,k2,k3);
  while( (k1 + k2 + k3 - 1 > 0.001) || (1 - k1 - k2 - k3 > 0.001) ){ // test if k1+k2+k3=1
    fprintf(stderr,"\nSorry, k1+k2+k3==%.5f != 1\nPlease input the weight k1, k2 and k3 again:\n",k1+k2+k3);
    scanf("%f %f %f",&k1,&k2,&k3);  
    fprintf(stderr,"k1 = %.5f, k2 = %.5f, k3 = %.5f\n",k1,k2,k3);
  }
 

  // @Part.2 input 
  // 读入图像的rgb灰度值
  fprintf(stderr,"\n------------------Part.2 Input-------------------\n");
  fprintf(stderr, "Reading RGB data from image binary file...\n");

  FILE *infile;
  infile = fopen(argv[1],"rb");  
  int w,h;
  fread(&w,sizeof(int),1,infile);
  fread(&h,sizeof(int),1,infile);
  fprintf(stderr,"The image's size is %d * %d\n", w,h);

  NEWDATA ***input;  
  input = (NEWDATA***)malloc(3 * sizeof(NEWDATA**));

  int i,j;
  for(i=0;i<3;i++){
    input[i] = (NEWDATA**)malloc((ROW+2) * sizeof(NEWDATA*));
    for(j=0;j<(ROW+2);j++){
      input[i][j] = (NEWDATA*)malloc((COL+2) * sizeof(NEWDATA));    
    }
  }
 
  // 初始化为0 
  for(i=0;i<3;i++){
    for(j=0;j<(COL+2);j++){
      input[i][0][j] = 0;
      input[i][ROW+1][j] = 0;
    }
    for(j=0;j<(ROW+2);j++){
      input[i][j][0] = 0;
      input[i][j][COL+1] = 0;
    }
  }
  
  // 读取数据
  for(j=0;j<3;j++){
    for(i=1;i<(ROW+1);i++){
      fread(input[j][i]+sizeof(NEWDATA),sizeof(NEWDATA),COL,infile);
    }
  }
  fclose(infile);


  // @Part.3 output
  // 进行卷积的计算和结果的写入
  fprintf(stderr,"\n------------------Part.3 Output------------------\n");
  fprintf(stderr, "Calculating the convolution and saving the value to binary file...\n");

  NEWDATA *y; //ROW y
  y = (NEWDATA*)malloc((COL) * sizeof(NEWDATA));
   
  FILE *out_y;
  out_y = fopen(argv[2],"wb");

  w = COL;
  h = ROW;
// printf("%d\n",w);
// printf("%d\n",h);
  fwrite(&w,sizeof(int),1,out_y);
  fwrite(&h,sizeof(int),1,out_y);
  
  fprintf(stderr,"-----------------------------------Calculating y1\n");  
  // mean_filter
  for(i=0;i<ROW;i++){
    calcul_y(y,mean_type,input,k1,k2,k3,out_y,i);
  }

  fprintf(stderr,"-----------------------------------Calculating y2\n"); 
  // guassian_filter
  for(i=0;i<ROW;i++){
    calcul_y(y,guassian_type,input,k1,k2,k3,out_y,i);
  }

  fprintf(stderr,"-----------------------------------Calculating y3\n"); 
  // highpass_filter
  for(i=0;i<ROW;i++){
    calcul_y(y,highpass_type,input,k1,k2,k3,out_y,i);
  }

  fprintf(stderr,"-----------------------------------Calculating y4\n");
  // laplacian_filter
  for(i=0;i<ROW;i++){
    calcul_y(y,laplacian_type,input,k1,k2,k3,out_y,i);
  }

  fclose(out_y);  
  fprintf(stderr,"\nThe run time of Section.2 is:");
  return 0;
}
