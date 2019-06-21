TRAP   x23         ; Input from the keyboard.
ADD    R1,R0,#0    ; Make room for another input.
TRAP   x23         ; Input another character.
ADD    R0,R1,R0    ; Add the two inputs.
TRAP   x21         ; Display result on the monitor.
TRAP   x25         ; Halt.
