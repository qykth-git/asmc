include consx.inc

	.code

togetbitflag PROC USES ebx tobj:PTR S_TOBJ, count, flag
	mov ebx,flag
	mov eax,count
	mov ecx,eax
	dec eax
	shl eax,4
	add eax,tobj
	mov edx,eax
	xor eax,eax
	.while	ecx
		.if bx & [edx]
			or al,1
		.endif
		shl eax,1
		sub edx,SIZE S_TOBJ
		dec ecx
	.endw
	shr eax,1
	ret
togetbitflag ENDP

	END
