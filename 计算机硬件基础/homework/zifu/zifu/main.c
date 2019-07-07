#include<stdio.h>
#include<stdlib.h>
int main()
{
    unsigned char s[10] = "王钟毓";
    int w,q,ofs;
    FILE *fp;
    int output[16][48];
    unsigned char u[32];
    q = s[0] - 0xA1;
    w = s[1] - 0xA1;
    ofs = q*94 + w + 256;
    if((fp = fopen("mhzk16c.txt","rb")) == NULL)
    {
        printf("The File Open Error !\n");
        exit(0);
    }
    fseek(fp,ofs*32L,SEEK_SET);
    fread(u, 1, 32, fp);
    int i,j,m;
    for(i=0;i<16;i++)
        for(j=0;j<48;j++)
            output[i][j] = 0;
    for(j=0;j<16;j++)
    {
        m=0x80;
        for(i=0;i<8;i++){
            if(u[j*2+0] & m)
            {
                output[i][j] = 1;
            }
            m >>= 1 ;
        }
        m = 0x80;
        for(i=0;i<8;i++)
        {
            if(u[j*2+1] & m)
            {
                output[i+8][j] = 1;
            }
            
            m >>= 1;
        }
        printf("\n");
    }
    for(i=0;i<16;i++)
    {
        for(j=0;j<48;j++)
            if(output[i][j]==1)
                printf("*");
            else
                printf(".");
        printf("\n");
    }
}

