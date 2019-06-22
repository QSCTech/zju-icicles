;
; Program to multiply an integer by the constant 6.
; Before execution, an integer must be stored in NUMBER.

        .ORIG   x3050
        LD      R1,SIX
        LD      R2,NUMBER
        AND     R3,R3,#0      ; Clear R3. It will
                              ; contain the product.
; The inner loop
;
AGAIN   ADD     R3,R3,R2
        ADD     R1,R1,#-1     ; R1 keeps track of
        BRp     AGAIN         ; the iterations
;
        HALT
;
NUMBER  .BLKW   1
SIX     .FILL   x0006
;
        .END
