; SCPUTA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    option win64:nosave

_scputa proc frame x:int_t, y:int_t, l:int_t, a:uchar_t

  local NumberOfAttrsWritten:dword

    mov   eax,edx
    movzx edx,r9b
    movzx r9d,al
    shl   r9d,16
    mov   r9b,cl

    FillConsoleOutputAttribute(_confh, dx, r8d, r9d, &NumberOfAttrsWritten)
    ret

_scputa endp

    END
