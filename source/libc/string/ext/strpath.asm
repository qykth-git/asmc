include string.inc

	.code

strpath PROC string:LPSTR
	strfn ( string )
	cmp	eax,string
	je	@F
	mov	byte ptr [eax-1],0
	mov	eax,string
@@:
	ret
strpath ENDP

	END
