include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isalnum PROC char
	mov	eax,[esp+4]
	mov	al,__ctype[eax+1]
	and	eax,_UPPER or _LOWER or _DIGIT
	ret	4
isalnum ENDP

	END
