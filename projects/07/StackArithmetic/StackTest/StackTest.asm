D=A
@ARG
A=M
M=D
@SP
M=M+1
@17
D=A
@R5
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@R13
M=D
@SP
A=M-1
A=A-1
D=M
@R13
D=M-D
@RETURN_EQ_3
D;JEQ
@SP
A=M-1
A=A-1
M=0
@DEC_SP_3
0;JMP
(RETURN_EQ_3)
@SP
A=M-1
A=A-1
M=-1
(DEC_SP_3)
@SP
M=M-1
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@16
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@R13
M=D
@SP
A=M-1
A=A-1
D=M
@R13
D=M-D
@RETURN_EQ_6
D;JEQ
@SP
A=M-1
A=A-1
M=0
@DEC_SP_6
0;JMP
(RETURN_EQ_6)
@SP
A=M-1
A=A-1
M=-1
(DEC_SP_6)
@SP
M=M-1
@16
D=A
@SP
A=M
M=D
@SP
M=M+1
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@R13
M=D
@SP
A=M-1
A=A-1
D=M
@R13
D=M-D
@RETURN_EQ_9
D;JEQ
@SP
A=M-1
A=A-1
M=0
@DEC_SP_9
0;JMP
(RETURN_EQ_9)
@SP
A=M-1
A=A-1
M=-1
(DEC_SP_9)
@SP
M=M-1
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@R13
M=D
@SP
A=M-1
A=A-1
D=M
@R13
D=D-M
@RETURN_LT_12
D;JLT
@SP
A=M-1
A=A-1
M=0
@DEC_SP_12
0;JMP
(RETURN_LT_12)
@SP
A=M-1
A=A-1
M=-1
(DEC_SP_12)
@SP
M=M-1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@R13
M=D
@SP
A=M-1
A=A-1
D=M
@R13
D=D-M
@RETURN_LT_15
D;JLT
@SP
A=M-1
A=A-1
M=0
@DEC_SP_15
0;JMP
(RETURN_LT_15)
@SP
A=M-1
A=A-1
M=-1
(DEC_SP_15)
@SP
M=M-1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@R13
M=D
@SP
A=M-1
A=A-1
D=M
@R13
D=D-M
@RETURN_LT_18
D;JLT
@SP
A=M-1
A=A-1
M=0
@DEC_SP_18
0;JMP
(RETURN_LT_18)
@SP
A=M-1
A=A-1
M=-1
(DEC_SP_18)
@SP
M=M-1
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@R13
M=D
@SP
A=M-1
A=A-1
D=M
@R13
D=D-M
@RETURN_GT_21
D;JGT
@SP
A=M-1
A=A-1
M=0
@DEC_SP_21
0;JMP
(RETURN_GT_21)
@SP
A=M-1
A=A-1
M=-1
(DEC_SP_21)
@SP
M=M-1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@R13
M=D
@SP
A=M-1
A=A-1
D=M
@R13
D=D-M
@RETURN_GT_24
D;JGT
@SP
A=M-1
A=A-1
M=0
@DEC_SP_24
0;JMP
(RETURN_GT_24)
@SP
A=M-1
A=A-1
M=-1
(DEC_SP_24)
@SP
M=M-1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@R13
M=D
@SP
A=M-1
A=A-1
D=M
@R13
D=D-M
@RETURN_GT_27
D;JGT
@SP
A=M-1
A=A-1
M=0
@DEC_SP_27
0;JMP
(RETURN_GT_27)
@SP
A=M-1
A=A-1
M=-1
(DEC_SP_27)
@SP
M=M-1
@57
D=A
@SP
A=M
M=D
@SP
M=M+1
@31
D=A
@SP
A=M
M=D
@SP
M=M+1
@53
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
A=A-1
M=D+M
@SP
M=M-1
@112
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
A=A-1
M=M-D
@SP
M=M-1
@SP
A=M-1
D=M
M=-D
@SP
A=M-1
D=M
A=A-1
M=M&D
@SP
M=M-1
@82
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
A=A-1
M=M|D
@SP
M=M-1
@SP
A=M-1
D=M
M=!D