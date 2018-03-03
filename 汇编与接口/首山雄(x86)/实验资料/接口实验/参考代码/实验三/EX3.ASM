DATA_SEG	SEGMENT
TABLE	DW	524,588,660,698,784,880,988
DATA_SEG	ENDS
STACK_SEG	SEGMENT		STACK
STA	DB	20 DUP(?)
TOP	EQU	LENGTH STA
STACK_SEG	ENDS
CODE_SEG	SEGMENT
	assume	cs:CODE_SEG,ds:DATA_SEG
	assume	ss:STACK_SEG
main	proc	far
	mov	ax,DATA_SEG
	mov	ds,ax
	mov	es,ax
	mov	ax,STACK_SEG
	mov	ss,ax
	mov	ax,top
	mov	sp,ax

	mov al,0b6h	;b6h＝10110110b
	out 43h,al	;写入控制字

start:	mov	ah,01
	int	21h
	cmp	al,38h
	jz	finish
	
	sub	al,31h
	shl	al,01
	mov	bl,al
	mov	bh,00
	mov	ax,3234h
	mov	dx,12h
	div	word ptr [TABLE+bx]
	
	call	speaker			;设置扬声器音调
	call	speakon			;打开扬声器声音
	call	delay			;
	call	speakoff		;关闭扬声器声音

	jmp	start

finish:	mov	ah,4ch
	int	21h
main	endp

speaker	proc
	push ax
	out 42h,al	;写入低8位计数值
	mov al,ah
	out 42h,al	;写入高8位计数值
	pop ax
	ret
speaker	endp

speakon	proc
	push ax
	in al,61h	;PB端口的地址为61H
	or al,03h	;D1D0＝PB1PB0＝11B，其他位不变
	out 61h,al
	pop ax
	ret
speakon	endp

delay	proc
	push ax
	push cx
	mov ax,0fffh
 x1:	mov cx,0ffffh
 x2:	dec cx
	jnz x2
	dec ax
	jnz x1
	pop cx
	pop ax
	ret
delay	endp

speakoff	proc
	push ax
	in al,61h	;PB端口的地址为61H
	and al,0fch	;D1D0＝PB1PB0＝00B，其他位不变
	out 61h,al
	pop ax
	ret
speakoff	endp

CODE_SEG	ENDS
	end	main
