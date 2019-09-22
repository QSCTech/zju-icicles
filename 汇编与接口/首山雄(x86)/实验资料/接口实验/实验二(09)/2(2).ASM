.MODEL SMALL
.data
Port_A DW 0DE00H
Port_B DW 0DE01H
Port_C DW 0DE02H
Port_Ctrl DW 0DE03H

.CODE
.STARTUP

	MOV DX,0DE03H   ; set control 
	MOV AL,0B0H
	OUT DX,AL
    MOV DX,0DE02H   ; set pc4=0
    IN  AL,DX
    AND AL,0EFH
    OUT DX,AL
    MOV CX,000AH
    
L1:	
DEC CX
MOV BX,CX
    MOV DX,0DE02H   ; check pc5
    IN  AL,DX
    AND AL,20H
    CMP AL,20H
    JNZ L1
	MOV DX,0DE00H   ; read port A
	IN  AL,DX
	MOV CX,0FFFFH
L2:
	DEC CX
	JNZ L2
    MOV DX,0DE01H
OUT DX,AL
MOV CX,BX
CMP CX,0000H
    JNZ L1

EXIT:
	MOV AH,4CH
	INT 21H


.EXIT
END

 
