.code
Instruction proc uses rsi rdi rbx
mov rdi,rsp
pushfq
mov rsi,rsp
I = 0
for op1,<rcx,rdx,r8,r9,r10,r11,rax>
for op2,<rbx,r12,r13,r14,r15,rcx,rdx,r8,r9,r10,r11,rax>
mov rsp,rsi
popfq
I = I + 1
endm
endm
mov rsp,rdi
ret
Instruction endp
end