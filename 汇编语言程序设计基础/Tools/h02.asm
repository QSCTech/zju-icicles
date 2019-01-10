data segment
upper db "Upper case", 0Dh, 0Ah, "$"
lower db "Lower case", 0Dh, 0Ah, "$"
data ends
code segment

assume cs:code, ds:data
main:
   mov ax, data
   mov ds, ax
   mov ah, 1
   int 21h;  AL=getchar()
   cmp al, 'A'
   jae maybe_upper
   jmp not_upper
maybe_upper:
   cmp al, 'Z'
   jbe is_upper
not_upper:
   cmp al, 'a'
   jb exit
   cmp al, 'z'
   ja exit
   jmp is_lower
is_upper:
   mov ah, 9
   mov dx, offset upper
   int 21h
   jmp exit
is_lower:
   mov ah, 9  
   mov dx, offset lower
   int 21h
exit:
   mov ah, 4Ch
   int 21h
code ends
end main