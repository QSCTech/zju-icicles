dseg	segment
msg	db	'Hello!',0dh,0ah,'$'
disp	db	'pci card interrupt!',0dh,0ah,'$'
cscs	dw	0
ipip	dw	0
status	db	0
stat	db	0
dseg	ends
;----------------
cseg	segment
	assume	cs:cseg,ds:dseg
main	proc	far

	mov	ax,dseg
	mov	ds,ax
	mov	es,ax
cli
	lea	dx,msg
	mov	ah,09h
	int	21h

	
;取原中断，保存 int 72h
	mov	ax,3572h
	int	21h
	mov	cscs,es
	mov	ipip,bx
;设置新中断
	mov	ax,cs
	mov	ds,ax
	mov	dx,offset ints
	mov	ax,2572h
	int	21h

;设置ds,es
	mov	ax,dseg
	mov	ds,ax
	mov	es,ax
	
;使能9052
	mov	dx,0dd80h + 4ch
	in	al,dx
	mov	status,al
	or	al,5bh
	out	dx,al
	mov	dx,0dd80h + 4dh
	in	al,dx
	or	al,0ch
	out	dx,al
;开屏蔽
	in	al,0a1h
	mov	stat,al
	and	al,11111011B
	out	0a1h,al

	mov	cx,0h

	sti

;4:中断处理
lp:	cmp	cx,0ah
	jnz	lp

	cli
	mov	ax,dseg
	mov	ds,ax
	mov	es,ax
;5:屏蔽
	mov	al,stat
	out	0a1h,al

;关闭9052
	mov	dx, 0dd80h + 4ch
	mov	al,status
	out	dx,al

;6:恢复原中断
	mov	dx,ipip
	mov	ax,cscs
	mov	ds,ax
	mov	ax,2572h
	int	21h
	sti
	mov	ah,4ch
	int	21h
main	endp
ints	proc	far
	cli
;1:保护现场
	push	dx
	push	ax

;2:中断处理
	lea	dx,disp
	mov	ah,9
	int	21h

	inc	cx
	
;3:中断结束
	mov	al,20h
	out	0a0h,al
	out	20h,al

	mov	dx,0dd80h + 4dh
	in	al,dx
	or	al,0ch
	out	dx,al
;4:恢复现场
	pop	ax
	pop	dx
	sti
;5:IRET
	iret
ints	endp
cseg	ends
	end	main
