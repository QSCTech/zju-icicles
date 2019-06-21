; This algorithm takes a sequence of ASCII digits typed by the user, 
; converts it into a binary value by calling the ASCIItoBinary 
; subroutine and pushes the binary value onto the stack.  
; 
PushValue         LEA       R1,ASCIIBUFF  ; R1 points to string being 
                  LD        R2,MaxDigits  ; generated
;
ValueLoop         ADD       R3,R0,xFFF6   ; Test for carriage return
                  BRz       GoodInput
                  ADD       R2,R2,#0
                  BRz       TooLargeInput
                  ADD       R2,R2,#-1     ; Still room for more digits
                  STR       R0,R1,#0      ; Store last character read
                  ADD       R1,R1,#1     
                  GETC
                  OUT                     ; Echo it
                  BRnzp     ValueLoop
;
GoodInput         LEA       R2,ASCIIBUFF
                  NOT       R2,R2
                  ADD       R2,R2,#1
                  ADD       R1,R1,R2      ; R1 now contains no. of char.
                  JSR       ASCIItoBinary
                  JSR       PUSH
                  BRnzp     NewCommand
;
TooLargeInput     GETC                    ; Spin until carriage return
                  OUT
                  ADD       R3,R0,xFFF6
                  BRnp      TooLargeInput
                  LEA       R0,TooManyDigits
                  PUTS
                  BRnzp     NewCommand
TooManyDigits     .FILL     x000A
                  .STRINGZ "Too many digits"
MaxDigits         .FILL     x0003
