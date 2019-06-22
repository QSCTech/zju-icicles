;
;  This algorithm takes an ASCII string of three decimal digits and 
;  converts it into a binary number.  R0 is used to collect the result.
;  R1 keeps track of how many digits are left to process.  ASCIIBUFF
;  contains the most significant digit in the ASCII string.
;
ASCIItoBinary  AND    R0,R0,#0      ; R0 will be used for our result 
               ADD    R1,R1,#0      ; Test number of digits.
               BRz    DoneAtoB      ; There are no digits
;
               LD     R3,NegASCIIOffset  ; R3 gets xFFD0, i.e., -x0030
               LEA    R2,ASCIIBUFF
               ADD    R2,R2,R1
               ADD    R2,R2,#-1     ; R2 now points to "ones" digit
;              
               LDR    R4,R2,#0      ; R4 <-- "ones" digit
               ADD    R4,R4,R3      ; Strip off the ASCII template
               ADD    R0,R0,R4      ; Add ones contribution
;
               ADD    R1,R1,#-1
               BRz    DoneAtoB      ; The original number had one digit
               ADD    R2,R2,#-1     ; R2  now points to "tens" digit
;
               LDR    R4,R2,#0      ; R4 <-- "tens" digit
               ADD    R4,R4,R3      ; Strip off ASCII  template
               LEA    R5,LookUp10   ; LookUp10 is BASE of tens values
               ADD    R5,R5,R4      ; R5 points to the right tens value
               LDR    R4,R5,#0
               ADD    R0,R0,R4      ; Add tens contribution to total
;
               ADD    R1,R1,#-1
               BRz    DoneAtoB      ; The original number had two digits
               ADD    R2,R2,#-1     ; R2 now points to "hundreds" digit
;        
               LDR    R4,R2,#0      ; R4 <-- "hundreds" digit
               ADD    R4,R4,R3      ; Strip off ASCII template
               LEA    R5,LookUp100  ; LookUp100 is hundreds BASE
               ADD    R5,R5,R4      ; R5 points to hundreds value
               LDR    R4,R5,#0
               ADD    R0,R0,R4      ; Add hundreds contribution to total
;         
DoneAtoB       RET
NegASCIIOffset .FILL  xFFD0
ASCIIBUFF      .BLKW  4
LookUp10       .FILL  #0
               .FILL  #10
               .FILL  #20
               .FILL  #30
               .FILL  #40
               .FILL  #50
               .FILL  #60
               .FILL  #70
               .FILL  #80
               .FILL  #90
;
LookUp100      .FILL  #0
               .FILL  #100
               .FILL  #200
               .FILL  #300
               .FILL  #400
               .FILL  #500
               .FILL  #600
               .FILL  #700
               .FILL  #800
               .FILL  #900
