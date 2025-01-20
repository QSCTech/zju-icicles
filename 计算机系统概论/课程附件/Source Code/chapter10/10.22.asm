;
;  The Calculator, Main Algorithm
;
                     LEA       R6,StackBase  ; Initialize the Stack.
                     ADD       R6,R6,#1     ; R6 is stack pointer
                     LEA       R0,PromptMsg
                     PUTS
                     GETC
                     OUT
;                                          
; Check the command
;
Test                 LD        R1,NegX       ; Check for X   
                     ADD       R1,R1,R0
                     BRz       Exit
;
                     LD        R1,NegC       ; Check for C   
                     ADD       R1,R1,R0
                     BRz       OpClear       ; See Figure 10.27
;
                     LD        R1,NegPlus    ; Check for +   
                     ADD       R1,R1,R0
                     BRz       OpAdd         ; See Figure 10.10
;
                     LD        R1,NegMult    ; Check for *   
                     ADD       R1,R1,R0
                     BRz       OpMult        ; See Figure 10.14
;
                     LD        R1,NegMinus   ; Check for -   
                     ADD       R1,R1,R0
                     BRz       OpNeg         ; See Figure 10.15
;
                     LD        R1,NegD       ; Check for D   
                     ADD       R1,R1,R0
                     BRz       OpDisplay     ; See Figure 10.26
;
; Then we must be entering an integer
;
                     BRnzp     PushValue     ; See Figure 10.23
;
NewCommand           LEA       R0,PromptMsg
                     PUTS
                     GETC
                     OUT
                     BRnzp     Test
Exit                 HALT
PromptMsg            .FILL     x000A
                     .STRINGZ "Enter a command:"
NegX                 .FILL     xFFA8
NegC                 .FILL     xFFBD
NegPlus              .FILL     xFFD5
NegMinus             .FILL     xFFD3
NegMult              .FILL     xFFD6
NegD                 .FILL     xFFBC
