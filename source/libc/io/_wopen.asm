; _WOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc

.code

_wopen proc path:LPWSTR, oflag:SINT, args:VARARG

ifdef __UNIX__
    mov ecx,[rax+4]
    _wsopen( path, oflag, SH_DENYNO, ecx )
else
    _wsopen( path, oflag, SH_DENYNO, args )
endif
    ret

_wopen endp

    end
