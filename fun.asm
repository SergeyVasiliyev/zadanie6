extern pow
section .data
    f_1 dq 0.35
    f_2 dq -0.95
    f_3 dq 2.7
    f_4 dq 3.0
    f_5 dq 2.0
section .text

global f1
global f2 
global f3
global f1_der
global f2_der
global f3_der

f1: ;0.35x^2 - 0.95x + 2.7
    push ebp
    mov ebp, esp
    finit
    fld qword[f_1]
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fmulp
    fmulp
    fld qword[f_2]
    fld qword[ebp + 8]
    fmulp
    faddp
    fld qword[f_3]
    faddp
    leave 
    ret
    
f2: ;3x + 1
    push ebp
    mov ebp, esp
    finit 
    fld qword[ebp + 8]
    fld qword[f_4]
    fmulp
    fld1
    faddp
    leave
    ret
    
f3: ;1 / (x + 2)
    push ebp
    mov ebp, esp
    finit
    fld1
    fld qword[ebp + 8]
    fld qword[f_5]
    faddp
    fdivp
    leave
    ret
