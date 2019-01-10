ASSUME CS:CODE, DS:DATA
;define the data segment
DATA SEGMENT
	GREEN_HIGH   	DB  0
    GREEN_LOW   	DB  0
    BLUE_H   		DB  0
    BLUE_M   		DB  0
    BLUE_L   		DB  0
    HIGH_PART  		DW  0   
    LOW_PART  		DW  0   
    NUM  			DB  0  
DATA ENDS
;the main code
CODE SEGMENT
START:
    MOV  AX, DATA
    MOV  DS, AX
    ;the address of the display buffer 
    MOV  AX, 0B800H
    MOV  ES, AX
	;initialize the loop condition
    MOV  NUM, 0
    MOV  LOW_PART, 0
	;loop to print the ASCII table
OUT_LOOP:
    MOV  HIGH_PART, 0
IN_LOOP:
    CALL CTRL_ROW_COL
    CALL PRINT
    ADD  HIGH_PART, 160
    INC  NUM
	MOV  AH, 0
	MOV	 AL, NUM
    CMP  AL, 0
	; if NUM is 0, finish the program
    JE   FINISH
    MOV  BL, 25
	; AL/25
    DIV  BL
    CMP  AH, 0
    JNE  IN_LOOP
    ADD  LOW_PART, 14
    JMP  OUT_LOOP
FINISH:
    MOV  AX, 4C00H
    INT  21H

;print each item function
PRINT  PROC
    MOV  AL, NUM
    MOV  AH, 12
    MOV  BX, HIGH_PART
    MOV  DI, LOW_PART
    MOV  ES:[BX + DI], AX
    MOV  AL, GREEN_HIGH
    MOV  AH, 10
    MOV  ES:[BX + DI + 2], AX
    MOV  AL, GREEN_LOW
    MOV  ES:[BX + DI + 4], AX
    MOV  AL, ' '
    MOV  ES:[BX + DI + 12], AX
    RET
PRINT  ENDP

;control the row and column information
;so that the ascii table is printed in 25 lines
CTRL_ROW_COL  PROC
    MOV  AL, NUM
    MOV  AH, 0
    MOV  BL, 16
    DIV  BL
    CMP  AL, 10
    JB   PART_1
    ADD  AL, 7
PART_1:
	ADD  AL, '0'
    MOV  GREEN_HIGH, AL
    CMP  AH, 10
    JB   PART_2
    ADD  AH, 7
PART_2:
	ADD  AH, '0'
    MOV  GREEN_LOW, AH
    MOV  AL, NUM
    MOV  AH, 0
	; AL/10
    MOV  BL, 10
    DIV  BL
    ADD  AH, '0'
    MOV  BLUE_L, AH
    MOV  AH, 0
    DIV  BL
    ADD  AH, '0'
    MOV  BLUE_M, AH
    ADD  AL, '0'
    MOV  BLUE_H, AL
    RET
CTRL_ROW_COL  ENDP
;the main code ends
	CODE ENDS
    END  START



