/* 编译及运行步骤:
把此文件复制到dosbox86\tc中, 
运行dosbox86
File->DOS Shell
cd \tc
tc
Alt+F选择File->Load->hexfile.c
Alt+C选择Compile->Compile to OBJ 编译
Alt+C选择Compile->Line EXE file 连接
Alt+R选择Run->Run 运行
 */
#include <stdio.h>
#include <stdlib.h>
#include <bios.h>
#include <io.h>
#define PageUp   0x4900
#define PageDown 0x5100
#define Home     0x4700
#define End      0x4F00
#define Esc      0x011B

void char2hex(char xx, char s[]) /* 把8位数转化成16进制格式 */
{
   char t[] = "0123456789ABCDEF";
   s[0] = t[(xx >> 4) & 0x0F]; /* 高4位 */
   s[1] = t[xx & 0x0F];        /* 低4位 */
}

void long2hex(long offset, char s[]) /* 把32位数转化成16进制格式 */
{
   int i;
   char xx;
   for(i=0; i<4; i++)
   {
      offset = _lrotl(offset, 8); /* 循环左移8位, 把高8位移到低8位 */
      xx = offset & 0xFF;         /* 高24位置0, 保留低8位 */
      char2hex(xx, &s[i*2]);      /* 把8位数转化成16进制格式 */
   }
}

void show_this_row(int row, long offset, char buf[], int bytes_on_row)
{  /* 显示当前一行:   行号       偏移    数组首地址      当前行字节数 */
   char far *vp = (char far *)0xB8000000;
   char s[]= 
      "00000000: xx xx xx xx|xx xx xx xx|xx xx xx xx|xx xx xx xx  ................";
   /*  |         |                                                |
       |         |                                                |
       00        10                                               59
       上述3个数字是竖线对应位置元素的下标;
       数组s的内容就是每行的输出格式:
       其中左侧8个0表示当前偏移地址;
       其中xx代表16进制格式的一个字节;
       其中s[59]开始共16个点代表数组buf各个元素对应的ASCII字符。
    */
   char pattern[] = 
      "00000000:            |           |           |                             ";
   int i;
   strcpy(s, pattern);
   long2hex(offset, s); /* 把32位偏移地址转化成16进制格式填入s左侧8个'0'处 */
   for(i=0; i<bytes_on_row; i++) /* 把buf中各个字节转化成16进制格式填入s中的xx处 */
   {
      char2hex(buf[i], s+10+i*3);
   }
   for(i=0; i<bytes_on_row; i++) /* 把buf中各个字节填入s右侧小数点处 */
   {
      s[59+i] = buf[i];
   }
   vp = vp + row*80*2;           /* 计算row行对应的视频地址 */
   for(i=0; i<sizeof(s)-1; i++)  /* 输出s */
   {
      vp[i*2] = s[i];
      if(i<59 && s[i] == '|')    /* 把竖线的前景色设为高亮度白色 */
         vp[i*2+1] = 0x0F;
      else                       /* 其它字符的前景色设为白色 */
         vp[i*2+1] = 0x07;
   }
}

void clear_this_page(void)       /* 清除屏幕0~15行 */
{
   char far *vp = (char far *)0xB8000000;
   int i, j;
   for(i=0; i<16; i++)           /* 汇编中可以使用rep stosw填入80*16个0020h */
   {
      for(j=0; j<80; j++)
      {
         *(vp+(i*80+j)*2) = ' ';
         *(vp+(i*80+j)*2+1) = 0;
      }
   }
}

void show_this_page(char buf[], long offset, int bytes_in_buf)
{  /* 显示当前页:   数组首地址       偏移        当前页字节数 */
   int i, rows, bytes_on_row;
   clear_this_page();
   rows = (bytes_in_buf + 15) / 16; /* 计算当前页的行数 */
   for(i=0; i< rows; i++)
   {
      bytes_on_row = (i == rows-1) ? (bytes_in_buf - i*16) : 16; /* 当前行的字节数 */
      show_this_row(i, offset+i*16, &buf[i*16], bytes_on_row); /* 显示这一行 */
   }
}

main()
{
   char filename[100];
   char buf[256];
   int  handle, key, bytes_in_buf;
   long file_size, offset, n;
   puts("Please input filename:");
   gets(filename); /* 输入文件名; 汇编中可以调用int 21h的0Ah功能 */
   handle = _open(filename, 0); /* 打开文件, 返回句柄; 
                                   汇编对应调用: 
                                   mov ah, 3Dh
                                   mov al, 0; 对应_open()的第2个参数, 表示只读方式
                                   mov dx, offset filename
                                   int 21h
                                   mov handle, ax
                                 */
   if(handle == -1)              /* 汇编中可以通过检查CF==1来判断上述打开文件有否成功 */
   {
      puts("Cannot open file!");
      exit(0); /* 汇编对应调用: 
                  mov ah, 4Ch
                  mov al, 0; 对应exit()中的参数
                  int 21h
                */
   }
   file_size = lseek(handle, 0, 2); /* 移动文件指针;
                                       汇编对应调用:
                                       mov ah, 42h
                                       mov al, 2; 对应lseek()的第3个参数,
                                                ; 表示以EOF为参照点进行移动
                                       mov bx, handle
                                       mov cx, 0; \ 对应lseek()的第2个参数
                                       mov dx, 0; /
                                       int 21h
                                       mov word ptr file_size[2], dx
                                       mov word ptr file_size[0], ax
                                     */
   offset = 0;
   do
   {
      n = file_size - offset;
      if(n >= 256)
         bytes_in_buf = 256;
      else
         bytes_in_buf = n;
      lseek(handle, offset, 0);      /* 移动文件指针;
                                       汇编对应调用:
                                       mov ah, 42h
                                       mov al, 0; 对应lseek()的第3个参数,
                                                ; 表示以偏移0作为参照点进行移动
                                       mov bx, handle
                                       mov cx, word ptr offset[2]; \cx:dx合一起构成
                                       mov dx, word ptr offset[0]; /32位值=offset
                                       int 21h
                                     */
      _read(handle, buf, bytes_in_buf); /* 读取文件中的bytes_in_buf个字节到buf中 
                                           汇编对应调用:
                                           mov ah, 3Fh
                                           mov bx, handle
                                           mov cx, bytes_in_buf
                                           mov dx, data
                                           mov ds, dx
                                           mov dx, offset buf
                                           int 21h
                                         */
      show_this_page(buf, offset, bytes_in_buf);
      key = bioskey(0); /* 键盘输入;
                           汇编对应调用:
                           mov ah, 0
                           int 16h
                         */
      switch(key)
      {
      case PageUp:
         offset = offset - 256;
         if(offset < 0)
            offset = 0;
         break;
      case PageDown:
         if(offset + 256 < file_size)
            offset = offset + 256;
         break;
      case Home:
         offset = 0;
         break;
      case End:
         offset = file_size - file_size % 256;
         if(offset == file_size)
            offset = file_size - 256;
         break;
      }
   } while(key != Esc);
   _close(handle); /* 关闭文件; 
                      汇编对应调用:
                      mov ah, 3Eh
                      mov bx, handle
                      int 21h
                    */
}
