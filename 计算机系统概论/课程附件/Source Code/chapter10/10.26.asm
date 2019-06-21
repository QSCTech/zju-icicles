; This algorithm calls BinarytoASCII to convert the 2's complement 
; number on the top of the stack into an ASCII character string, and
; then calls PUTS to display that number on the screen.
OpDisplay    JSR       POP         ; R0 gets the value to be displayed
             ADD       R5,R5,#0  
             BRp       NewCommand  ; POP failed, nothing on the stack.
             JSR       BinarytoASCII 
             LD        R0,NewlineChar
             OUT
             LEA       R0,ASCIIBUFF
             PUTS
             ADD       R6,R6,#-1   ; Push displayed number back on stack
             BRnzp     NewCommand
NewlineChar  .FILL     x000A
