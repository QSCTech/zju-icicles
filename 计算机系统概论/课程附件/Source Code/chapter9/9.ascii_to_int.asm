          LEA    R3,Binary   ; Initialize to first location
          LD     R6,ASCII    ; Template for line 05
          LD     R7,COUNT    ; Initialize to 10 
AGAIN     TRAP   x23         ; Get keyboard input
          ADD    R0,R0,R6    ; Strip ASCII template
          STR    R0,R3,#0    ; Store binary digit
          ADD    R3,R3,#1    ; Increment pointer
          ADD    R7,R7,#-1   ; Decrement COUNT.
          BRp    AGAIN       ; More characters?
          BRnzp  NEXT_TASK   ; 
ASCII     .FILL  xFFD0       ; Negative of x0030.
COUNT     .FILL  #10
Binary    .BLKW  #10
