;
;     Routine to check that the magnitude of a value is 
;     between -999 and +999.
;
RangeCheck    LD        R5,Neg999
              ADD       R4,R0,R5   ; Recall that R0 contains the 
              BRp       BadRange   ; result being checked.
              LD        R5,Pos999
              ADD       R4,R0,R5
              BRn       BadRange
              AND       R5,R5,#0   ; R5 <-- success
              RET
BadRange      ST        R7,Save    ; R7 is needed by TRAP/RET
              LEA       R0,RangeErrorMsg
              TRAP      x22        ; Output character string
              LD        R7,Save
              AND       R5,R5,#0   ; 
              ADD       R5,R5,#1   ; R5 <-- failure
              RET
Neg999        .FILL     #-999
Pos999        .FILL     #999
Save          .FILL     x0000
RangeErrorMsg .FILL     x000A
              .STRINGZ  "Error: Number is out of range."
