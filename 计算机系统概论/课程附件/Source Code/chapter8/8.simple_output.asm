START   LDI     R1, A         ; Test to see if 
        BRzp    START         ; output register is ready 
        STI     R0, B
        BRnzp   NEXT_TASK
A       .FILL   xFE04         ; Address of DSR
B       .FILL   xFE06         ; Address of DDR
