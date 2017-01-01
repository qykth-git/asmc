include stdio.inc
include io.inc
include errno.inc

	.code

	ASSUME	ebx: LPFILE

fseek	PROC USES ebx,
	fp:	LPFILE,
	off:	ULONG,
	whence: SIZE_T

	mov	ebx,fp
	mov	eax,whence
	.if	eax != SEEK_SET && eax != SEEK_CUR && eax != SEEK_END
		jmp	error
	.endif
	mov	edx,eax
	mov	eax,[ebx].iob_flag
	.if	!( eax & _IOREAD or _IOWRT or _IORW )
		jmp	error
	.endif
	and	eax,not _IOEOF
	mov	[ebx].iob_flag,eax
	.if	edx == SEEK_CUR
		ftell ( ebx )
		add	off,eax
		mov	whence,SEEK_SET
	.endif
	fflush( ebx )

	mov	eax,[ebx].iob_flag
	.if	eax & _IORW
		and	eax,not (_IOWRT or _IOREAD)
		mov	[ebx].iob_flag,eax
	.elseif eax & _IOREAD && eax & _IOMYBUF && !( eax & _IOSETVBUF )
		mov	[ebx].iob_bufsize,_MINIOBUF
	.endif

	mov	eax,[ebx].iob_file
	mov	eax,_osfhnd[eax*4]
	.if	SetFilePointer( eax, off, 0, whence ) == -1
		call	osmaperr
		jmp	toend
	.endif
	xor	eax,eax
toend:
	ret
error:
	mov	errno,EINVAL
	mov	eax,-1
	jmp	toend
fseek	ENDP

	END