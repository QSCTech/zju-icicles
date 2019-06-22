        POP      LD      R1,EMPTY      ; EMPTY <-- -x4000
                 ADD     R2,R6,R1
                 BRz     Failure
                 LDR     R0,R6,#0
                 ADD     R6,R6,#1
                 AND     R5,R5,#0
                 RET
        Failure  AND     R5,R5,#0
                 ADD     R5,R5,#1
                 RET
        EMPTY    .FILL   xC000
