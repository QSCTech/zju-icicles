      PUSH       LD      R1,MAX        ; MAX <-- -3FFB
                 ADD     R2,R6,R1
                 BRz     Failure
                 ADD     R6,R6,#-1
                 STR     R0,R6,#0
                 AND     R5,R5,#0
                 RET
      Failure    AND     R5,R5,#0
                 ADD     R5,R5,#1
                 RET
      MAX        .FILL   xC005
