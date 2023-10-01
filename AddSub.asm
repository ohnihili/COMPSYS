// Calculates R1 + R2 - R3 and stores the result in R0.
// (R0, R1, R2, R3 refer to RAM[0], RAM[1], RAM[2], and RAM[3], respectively.)

// Put your code here.

    @1
    D=M
    @2
    M=D+M
    D=M
    @3
    M=D-M
    D=M
    @0
    M=D
    @END
	0;JMP

(END)  
       @END
       0; JMP