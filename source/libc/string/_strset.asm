include string.inc

    .code

_strset proc dst:LPSTR, char:SINT

    mov ecx,dst
    mov eax,char
    .while byte ptr [ecx]

        mov [ecx],al
        inc ecx
    .endw
    mov eax,dst
    ret

_strset endp

    END
