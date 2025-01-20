dseg	segment
msg	db	"Hello!",13,10,"$"
dseg	ends
;----------------
cseg	segment
	assume	cs:cseg,ds:dseg
main	proc	far
	mov	ax,dseg
	mov	ds,ax
	mov	es,ax
	lea	dx,msg
	mov	ah,9
	int	21h
	;mov	cx,0

start:	mov	ah,01h
	int	16h

	jz	AA
	mov	ah,00h
	int	16h
	mov	dl,al
	mov	ah,02h
	int	21h
	JMP	start

AA:	MOV	DL,'G'
	MOV	AH,02H
	INT	21H
	JMP	START

off:	mov	ah,4ch
	int	21h
main	endp
cseg	ends
	end	main
