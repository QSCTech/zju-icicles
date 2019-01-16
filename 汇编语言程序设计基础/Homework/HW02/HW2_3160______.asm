.model small
.386
.stack 200h
.data                         
	num1     dw   0 ;整数1
	num2     dw   0 ;整数2
	product  dd   0 ;乘积

	buffer   db  10 ;0ah缓冲区大小
	k_size   db  ?  ;实际读入字数的格式，中断调用后，自动填入
	k_buffer db  10 dup(0)  ;键盘输入最多10个字符  
	asc_arr  db  "0123456789ABCDEF" ;输出数字时，需要的ASC码 
	    
.code
.STARTUP 
    
	call get_int
	mov num1, ax
	
	call crlf	
	call get_int
	mov num2, ax
	
	;扩展到32寄存器,
	;然后求乘积
	movzx eax, num1
	movzx ebx, num2
	mul ebx	
	mov product, eax
	
	call crlf
	movzx eax, num1
	mov ebx, 10
	call print_int ;显示第2个整数
	mov dl, '*'
	call print_char
	movzx eax, num2
	mov ebx, 10
	call print_int ;显示第2个整数
	
	mov dl, '='
	call print_char
	;显示10进制乘积
	call crlf
	mov eax, product
	mov ebx, 10
	call print_int
	;显示16进制乘积
	call crlf
	mov eax, product
	mov ebx, 16
	call print_int
	mov dl, 'H'
	call print_char
	;显示2进制乘积
	call crlf
	mov eax, product
	call print_bin
	mov dl, 'B'
	call print_char
.EXIT

;eax -整数 
;ebx -进制
print_int proc

	mov cx, 0   ;统计整数的位数
L_div:
    mov edx, 0  ;除法之前edx清0
    div ebx 
    push dx     ;余数入栈
    inc cx      ;统计位数+1
    cmp eax, 0  ;eax除尽
    jne L_div 
  
L_print:
    pop si      ;取出余数
	mov dl, asc_arr[si]
	mov ah, 2
	int 21h
    loop  L_print

	ret
print_int endp
;输入十进制字符串
;转换二进制,返回值ax	
get_int proc

	;0ah 键盘读入一个整数字符串
	lea dx, buffer
    mov ah,0ah
	int 21h
	
    mov ch,0
    mov cl, k_size;
	mov ax, 0 ; 整数初始0
	lea si, k_buffer
	
	mov dh, 0
	mov bx, 10
L_read:
    mul bx  ;乘10
    mov dl, [si]
    sub dl, '0'
    
	add ax, dx ;ax加上当前的数字
    inc si    
    loop L_read 

	ret
get_int endp
;输出一个换行
crlf proc
	push ax
	push dx
	
	mov dl, 0dh
	mov ah,2
	int 21h
	mov dl,0ah
	mov ah,2
	int 21h

	pop dx
	pop ax	
	ret
crlf endp
;显示一个整数的二进制
; eax - 整数
print_bin proc
	
	mov cx, 8 ;8组
L1:
	push cx
	mov cx, 4 ;一次显示4位
L2:	
	shl eax, 1
	jc is_1
	mov dl, '0' ;0
	call print_char
	jmp L2_next
is_1:
	mov dl, '1' ;1
	call print_char
L2_next:
	loop L2

	mov dl, ' ' ;显示一个空格
	call print_char

	pop cx
	loop L1

	mov dl, 8 ;退格
	call print_char
	
	ret
print_bin endp
;显示dl里面的字符
print_char proc
	push ax
	mov ah, 2
	int 21h
	pop ax
	ret
print_char endp
    end 
