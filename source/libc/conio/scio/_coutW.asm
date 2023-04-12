; _COUTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc
include string.inc

.code

_coutW proc format:wstring_t, argptr:vararg

  local cchWritten:ulong_t
  local stream:_iobuf
  local buffer[1024]:wchar_t

    .if ( _confh == -1 )

        xor eax,eax
    .else
        ;
        ; write character to console file handle
        ;
        mov stream._flag,_IOWRT or _IOSTRG
        mov stream._cnt,_INTIOBUF
        lea rax,buffer
        mov stream._ptr,rax
        mov stream._base,rax
        mov ecx,_woutput(&stream, format, &argptr)
        .if WriteConsoleW(_confh, stream._base, ecx, &cchWritten, NULL)
            mov eax,cchWritten
        .endif
    .endif
    ret

_coutW endp

    end