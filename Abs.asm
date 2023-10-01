// Calculates the absolute value of R1 and stores the result in R0.
// (R0, R1 refer to RAM[0], and RAM[1], respectively.)

// Put your code here.

    @1
    D=M
    @0
    M=D
    @abs
    M=D
    @END
    D;JGE

(NEG)
    @abs
    M=!M
    M=M+1
    D=M
    @0
    M=D
    @END
	0;JMP

(END)  
       @END
       0; JMP