include io.inc
include errno.inc
include stdlib.inc
include crtl.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_lseeki64 PROC handle:SINT, offs:QWORD, pos:UINT

	local	lpNewFilePointer:QWORD

	mov	r9,r8
	.if	getosfhnd( ecx ) != -1

		.if	!SetFilePointerEx( rax, edx, addr lpNewFilePointer, r9d )
			call	osmaperr
		.else
			mov	rax,lpNewFilePointer
		.endif
	.endif
	ret
_lseeki64 ENDP

	END