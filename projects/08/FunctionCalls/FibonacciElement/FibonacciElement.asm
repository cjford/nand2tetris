@256
D=A
@SP
M=D
@RETURN_Sys.init_0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M
A=A-1
A=A-1
A=A-1
A=A-1
A=A-1
D=A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.init
0;JMP
(RETURN_Sys.init_0)
(Main.fibonacci)
@ARG
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
@2
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
@RETURN_LT_4
D;JLT
@SP
A=M-1
A=A-1
M=0
@DEC_SP_4
0;JMP
(RETURN_LT_4)
@SP
A=M-1
A=A-1
M=-1
(DEC_SP_4)
@SP
M=M-1
@SP
A=M-1
D=M
@SP
M=M-1
@IF_TRUE
D;JNE
@IF_FALSE
0;JMP
(IF_TRUE)
@ARG
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@R13
M=D
@LCL
A=M
A=A-1
A=A-1
A=A-1
A=A-1
A=A-1
D=M
@R14
M=D
@SP
A=M-1
D=M
@SP
M=M-1
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@R13
A=M
A=A-1
D=M
@THAT
M=D
@R13
A=M
A=A-1
A=A-1
D=M
@THIS
M=D
@R13
A=M
A=A-1
A=A-1
A=A-1
D=M
@ARG
M=D
@R13
A=M
A=A-1
A=A-1
A=A-1
A=A-1
D=M
@LCL
M=D
@R14
A=M
0;JMP
(IF_FALSE)
@ARG
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
@2
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
@RETURN_Main.fibonacci_14
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M
A=A-1
A=A-1
A=A-1
A=A-1
A=A-1
A=A-1
D=A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(RETURN_Main.fibonacci_14)
@ARG
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
@1
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
@RETURN_Main.fibonacci_18
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M
A=A-1
A=A-1
A=A-1
A=A-1
A=A-1
A=A-1
D=A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(RETURN_Main.fibonacci_18)
@SP
A=M-1
D=M
A=A-1
M=D+M
@SP
M=M-1
@LCL
D=M
@R13
M=D
@LCL
A=M
A=A-1
A=A-1
A=A-1
A=A-1
A=A-1
D=M
@R14
M=D
@SP
A=M-1
D=M
@SP
M=M-1
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@R13
A=M
A=A-1
D=M
@THAT
M=D
@R13
A=M
A=A-1
A=A-1
D=M
@THIS
M=D
@R13
A=M
A=A-1
A=A-1
A=A-1
D=M
@ARG
M=D
@R13
A=M
A=A-1
A=A-1
A=A-1
A=A-1
D=M
@LCL
M=D
@R14
A=M
0;JMP