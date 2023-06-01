; _OUTPUT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include limits.inc
include wchar.inc
include fltintrn.inc
include winnls.inc

define BUFFERSIZE      512     ; ANSI-specified minimum is 509

define FL_SIGN         0x0001  ; put plus or minus in front
define FL_SIGNSP       0x0002  ; put space or minus in front
define FL_LEFT         0x0004  ; left justify
define FL_LEADZERO     0x0008  ; pad with leading zeros
define FL_LONG         0x0010  ; long value given
define FL_SHORT        0x0020  ; short value given
define FL_SIGNED       0x0040  ; signed data given
define FL_ALTERNATE    0x0080  ; alternate form requested
define FL_NEGATIVE     0x0100  ; value is negative
define FL_FORCEOCTAL   0x0200  ; force leading '0' for octals
define FL_LONGDOUBLE   0x0400  ; long double
define FL_WIDECHAR     0x0800
define FL_LONGLONG     0x1000  ; long long or REAL16 value given
define FL_I64          0x8000  ; 64-bit value given

define ST_NORMAL       0       ; normal state; outputting literal chars
define ST_PERCENT      1       ; just read '%'
define ST_FLAG         2       ; just read flag character
define ST_WIDTH        3       ; just read width specifier
define ST_DOT          4       ; just read '.'
define ST_PRECIS       5       ; just read precision specifier
define ST_SIZE         6       ; just read size specifier
define ST_TYPE         7       ; just read type specifier

ifdef FORMAT_VALIDATIONS
define NUMSTATES       (ST_INVALID + 1)
else
define NUMSTATES       (ST_TYPE + 1)
endif

externdef __lookuptable:byte

    .code

write_char proc private c:int_t, fp:LPFILE, pNumWritten:LPWORD

    ldr ecx,c
    ldr rdx,fp
    fputc( ecx, rdx )

    mov rcx,pNumWritten
    .if ( eax == -1 )
        mov [rcx],eax
    .else
        inc dword ptr [rcx]
    .endif
    ret

write_char endp

write_string proc private uses rbx string:LPSTR, len:SINT, fp:LPFILE, pNumwritten:ptr

    .for ( rbx = string : len > 0 : len-- )

        movzx ecx,byte ptr [rbx]
        inc rbx

        .ifd ( fputc( ecx, fp ) == -1 )

            mov rcx,pNumwritten
            mov [rcx],eax
           .break
        .else
            mov rcx,pNumwritten
            inc dword ptr [rcx]
        .endif
    .endf
    ret

write_string endp

write_multi_char proc private uses rbx c:SINT, num:SINT, fp:LPFILE, pNumWritten:ptr

    .for ( rbx = pNumWritten : num > 0 : num-- )

        .ifd ( fputc( c, fp ) == -1 )

            mov [rbx],eax
           .break
        .endif
        inc dword ptr [rbx]
    .endf
    ret

write_multi_char endp


_va_arg macro ap
if defined(__UNIX__) and defined(_AMD64_)
    dec argcnt
    .ifz
        mov ap,r13
    .endif
endif
    mov rax,ap
    add ap,size_t
    retm<[rax]>
    endm

ifdef _WIN64
ifdef __UNIX__
_output proc uses rbx r12 r13 r14 r15 fp:LPFILE, format:string_t, argptr:ptr
define flags        <r14d>
define precision    <r15d>
define arglist      <r12>
   .new argxmm      : ptr
   .new argcnt      : int_t     ; regargs + 1
else
_output proc uses rsi rdi rbx r12 fp:LPFILE, format:string_t, argptr:ptr
define flags        <edi>
define precision    <esi>
define arglist      <r12>
endif
else
_output proc uses esi edi ebx fp:LPFILE, format:string_t, arglist:ptr
define flags        <edi>
define precision    <esi>
endif

   .new charsout            : int_t = 0
   .new hexoff              : uint_t
   .new state               : uint_t = 0
   .new curadix             : uint_t
   .new prefix[2]           : uchar_t
   .new textlen             : uint_t = 0
   .new prefixlen           : uint_t
   .new no_output           : uint_t
   .new fldwidth            : uint_t
   .new bufferiswide        : uint_t = 0
   .new padding             : uint_t
   .new text                : string_t
   .new mbuf[MB_LEN_MAX+1]  : wint_t
   .new buffer[BUFFERSIZE]  : char_t

ifdef _WIN64
ifdef __UNIX__
    mov eax,[rdx]
    mov ecx,[rdx+4]
    add rax,[rdx+16]
    add rcx,[rdx+16]
    mov arglist,rax
    mov argxmm,rcx
    mov r13,[rdx+8]
    mov ecx,7
    mov eax,[rdx]
    shr eax,3
    sub ecx,eax
    mov argcnt,ecx
else
    mov arglist,r8
endif
endif

    .while 1

        lea   rcx,__lookuptable
        mov   rax,format
        inc   format
        movzx eax,byte ptr [rax]
        mov   edx,eax

        .break .if ( !eax || charsout > INT_MAX )

        .if ( eax >= ' ' && eax <= 'x' )

            mov al,[rcx+rax-32]
            and eax,15
        .else
            xor eax,eax
        .endif

        shl eax,3
        add eax,state
        mov al,[rcx+rax]
        shr eax,4
        and eax,0x0F
        mov state,eax

        .if ( eax <= 7 )

            .switch eax
            .case ST_NORMAL
                mov bufferiswide,0
                mov ecx,edx
ifndef __UNIX__
                .if isleadbyte( ecx )

                    write_char( ecx, fp, &charsout )

                    mov rax,format
                    inc format
                    movzx ecx,BYTE PTR [rax]
                .endif
endif
                write_char( ecx, fp, &charsout )
                .endc

            .case ST_PERCENT
                xor eax,eax
                mov no_output,eax
                mov fldwidth,eax
                mov prefixlen,eax
                mov bufferiswide,eax
                mov flags,eax
                mov precision,-1
                .endc

            .case ST_FLAG
                movzx eax,dl
                .switch pascal eax
                .case '+': or flags,FL_SIGN      ; '+' force sign indicator
                .case ' ': or flags,FL_SIGNSP    ; ' ' force sign or space
                .case '#': or flags,FL_ALTERNATE ; '#' alternate form
                .case '-': or flags,FL_LEFT      ; '-' left justify
                .case '0': or flags,FL_LEADZERO  ; '0' pad with leading zeros
                .endsw
                .endc

            .case ST_WIDTH
                .if ( dl == '*' )

                    mov eax,_va_arg(arglist)
                    .ifs ( eax < 0 )
                        or  flags,FL_LEFT
                        neg eax
                    .endif
                    mov fldwidth,eax

                .else

                    movsx edx,dl
                    imul  eax,fldwidth,10
                    add   eax,edx
                    add   eax,-48
                    mov   fldwidth,eax
                .endif
                .endc

            .case ST_DOT
                mov precision,0
               .endc

            .case ST_PRECIS
                mov ecx,precision
                .if ( dl == '*' )

                    mov ecx,_va_arg(arglist)
                    .ifs ( ecx < 0 )
                        mov ecx,-1
                    .endif
                .else
                    imul  eax,ecx,10
                    movsx ecx,dl
                    add   ecx,eax
                    add   ecx,-48
                .endif
                mov precision,ecx
               .endc

            .case ST_SIZE

                .switch edx
                .case 'l'
                    .if ( !( flags & FL_LONG ) )
                        or flags,FL_LONG
                       .endc
                    .endif

                    ; case ll => long long

                    and flags,NOT FL_LONG
                    or  flags,FL_LONGLONG
                   .endc

                .case 'L'
                    or  flags,FL_LONGDOUBLE or FL_I64
                   .endc

                .case 'I'
                    mov rax,format
                    mov cx,[rax]

                    .switch cl

                    .case '6'
                        .if ( ch != '4' )
                            .gotosw(2:ST_NORMAL)
                        .endif
                        or  flags,FL_I64
                        add rax,2
                        mov format,rax
                       .endc

                    .case '3'
                        .if ( ch != '2' )
                            .gotosw(2:ST_NORMAL)
                        .endif
                        and flags,not FL_I64
                        add rax,2
                        mov format,rax
                       .endc

                    .case 'd','i','o','u','x','X'
                        .endc
                    .default
                        .gotosw(2:ST_NORMAL)
                    .endsw
                    .endc
                .case 'h'
                    or flags,FL_SHORT
                   .endc
                .case 'w'
                    or flags,FL_WIDECHAR  ; 'w' => wide character
                .endsw
                .endc

            .case ST_TYPE

                mov eax,edx

                .switch eax

                .case 'b'
                    mov edx,_va_arg(arglist)
                    xor ecx,ecx
                    bsr ecx,edx
                    inc ecx
                    mov textlen,ecx
                    lea rbx,buffer
                    .repeat
                        xor eax,eax
                        shr edx,1
                        adc al,'0'
                        mov [rbx+rcx-1],al
                    .untilcxz
                    mov text,rbx
                    .endc

                .case 'C' ; ISO wide character
                    .if ( !( flags & ( FL_SHORT or FL_LONG or FL_WIDECHAR ) ) )
                        ;
                        ; CONSIDER: non-standard
                        ;
                        or flags,FL_WIDECHAR ; ISO std.
                    .endif

                .case 'c'
                    ;
                    ; print a single character specified by int argument
                    ;
                    _va_arg(arglist)
                    mov rcx,rax
                    lea rax,buffer
                    mov textlen,1 ; print just a single character
                    mov text,rax

ifndef __UNIX__
                    .if ( flags & ( FL_LONG or FL_WIDECHAR ) )

                        movzx edx,word ptr [rcx]
                        mov [rax],edx
                        WideCharToMultiByte( 0, 0, rax, 1, rax, 1, 0, 0 )
                    .else
endif
                        mov dl,[rcx]
                        mov [rax],dl
ifndef __UNIX__
                    .endif
endif
                    .endc

                .case 'S' ; ISO wide character string
                    .if ( !( flags & ( FL_SHORT or FL_LONG or FL_WIDECHAR ) ) )

                        or flags,FL_WIDECHAR
                    .endif
                .case 's'

                    ; print a string --
                    ; ANSI rules on how much of string to print:
                    ;   all if precision is default,
                    ;   min(precision, length) if precision given.
                    ; prints '(null)' if a null string is passed

                    mov rax,_va_arg(arglist)
                    mov ecx,precision
                    .if ( ecx == -1 )
                        mov ecx,INT_MAX
                    .endif
                    .if ( !rax )
                        lea rax,@CStr("(null)")
                        and flags,not ( FL_LONG or FL_WIDECHAR )
                    .endif
                    mov text,rax

                    .if ( flags & ( FL_LONG or FL_WIDECHAR ) )
                        mov bufferiswide,1
                        .repeat
                            .break .if ( word ptr [rax] == 0 )
                            add rax,2
                        .untilcxz
                    .else
                        .repeat
                            .break .if ( byte ptr [rax] == 0 )
                            inc rax
                        .untilcxz
                    .endif
                    sub rax,text
                    mov textlen,eax
                    .endc

                .case 'n'
                    _va_arg(arglist)
                    mov rdx,[rax-size_t]
                    mov eax,charsout
                    mov [rdx],eax
                    .if ( flags & FL_LONG )
                        mov no_output,1
                    .endif
                    .endc

ifndef _STDCALL_SUPPORTED

                .case 'E'
                .case 'G'
                .case 'A'
                    or  flags,_ST_CAPEXP  ; capitalize exponent
                    add dl,'a' - 'A'    ; convert format char to lower
                    ;
                    ; DROP THROUGH
                    ;
                .case 'e'
                .case 'f'
                .case 'g'
                .case 'a'
                    ;
                    ; floating point conversion -- we call cfltcvt routines
                    ; to do the work for us.
                    ;
                    or  flags,FL_SIGNED   ; floating point is signed conversion
                    lea rax,buffer      ; put result in buffer
                    mov text,rax
                    ;
                    ; compute the precision value
                    ;
                    .ifs ( precision < 0 )
                        mov precision,6       ; default precision: 6
                    .elseif ( !precision && dl == 'g' )
                        mov precision,1       ; ANSI specified
                    .endif
if defined(__UNIX__) and defined(_AMD64_)
                    mov rax,argxmm
                    add argxmm,16
else
                    mov rcx,arglist
                    add arglist,size_t
                    mov rax,[rcx]
endif
                    mov ebx,edx
                    mov edx,flags
                    and edx,_ST_CAPEXP
                    ;
                    ; do the conversion
                    ;
                    .if ( flags & FL_LONGDOUBLE )
ifndef _WIN64
                        add arglist,12
                        mov eax,ecx
endif
                        or edx,_ST_LONGDOUBLE
                        _cldcvt( rax, text, ebx, precision, edx )
                    .elseif ( flags & FL_LONGLONG )
ifndef _WIN64
                        add arglist,8
                        mov eax,ecx
endif
                        or edx,_ST_QUADFLOAT
                        _cqcvt( rax, text, ebx, precision, edx )
                    .else
ifndef _WIN64
                        add arglist,4
endif
                        or edx,_ST_DOUBLE
if defined(__UNIX__) and defined(_AMD64_)
                        _cfltcvt( rax, text, ebx, precision, edx )
else
                        _cfltcvt( rcx, text, ebx, precision, edx )
endif
                    .endif
                    ;
                    ; '#' and precision == 0 means force a decimal point
                    ;
                    .if ( ( flags & FL_ALTERNATE ) && !precision )

                        _forcdecpt( text )
                    .endif
                    ;
                    ; 'g' format means crop zero unless '#' given
                    ;
                    .if ( bl == 'g' && !( flags & FL_ALTERNATE ) )

                        _cropzeros( text )
                    .endif
                    ;
                    ; check if result was negative, save '-' for later
                    ; and point to positive part (this is for '0' padding)
                    ;
                    mov rcx,text
                    mov al,[rcx]
                    .if ( al == '-' )

                        or  flags,FL_NEGATIVE
                        inc text
                    .endif
                    strlen( text ) ; compute length of text
                    mov textlen,eax
                    .endc

endif ; _STDCALL_SUPPORTED

                .case 'd'
                .case 'i'
                    ;
                    ; signed decimal output
                    ;
                    or  flags,FL_SIGNED
                .case 'u'
                    mov curadix,10
                    jmp COMMON_INT

                .case 'p'
                    ;
                    ; write a pointer -- this is like an integer or long
                    ; except we force precision to pad with zeros and
                    ; output in big hex.
                    ;
                    mov precision,size_t * 2
ifdef _WIN64
                    or  flags,FL_I64
endif
                    ;
                    ; DROP THROUGH to hex formatting
                    ;
                .case 'X' ; unsigned upper hex output
                    ;
                    ; set hexadd for uppercase hex
                    ;
                    mov hexoff,'A'-'9'-1
                    jmp COMMON_HEX

                .case 'x'
                    ;
                    ; unsigned lower hex output
                    ;
                    mov hexoff,'a'-'9'-1
                    ;
                    ; DROP THROUGH TO COMMON_HEX
                    ;
                    COMMON_HEX:

                    mov curadix,16
                    .if ( flags & FL_ALTERNATE )
                        ;
                        ; alternate form means '0x' prefix
                        ;
                        mov eax,'x' - 'a' + '9' + 1
                        add eax,hexoff
                        mov prefix,'0'
                        mov prefix[1],al
                        mov prefixlen,2
                    .endif
                    jmp COMMON_INT

                .case 'o' ; unsigned octal output
                    mov curadix,8
                    .if ( flags & FL_ALTERNATE )
                        ;
                        ; alternate form means force a leading 0
                        ;
                        or flags,FL_FORCEOCTAL
                    .endif
                    ;
                    ; DROP THROUGH to COMMON_INT
                    ;
                   COMMON_INT:
                    ;
                    ; This is the general integer formatting routine.
                    ; Basically, we get an argument, make it positive
                    ; if necessary, and convert it according to the
                    ; correct radix, setting text and textlen
                    ; appropriately.
                    ;
                    _va_arg(arglist)
                    xor edx,edx
                    mov rcx,rax
                    mov eax,[rcx]
                    .if ( flags & ( FL_I64 or FL_LONGLONG ) )

                        mov edx,[rcx+4]
ifndef _WIN64
                        add arglist,size_t
endif
                    .endif

                    .if ( flags & FL_SHORT )

                        .if ( flags & FL_SIGNED )
                            ; sign extend
                            movsx eax,ax
                        .else
                            ; zero-extend
                            movzx eax,ax
                        .endif

                    .elseif ( flags & FL_SIGNED )

                        .if ( !( flags & ( FL_I64 or FL_LONGLONG ) ) )

                            .ifs ( eax < 0 )

                                dec edx
                                or  flags,FL_NEGATIVE
                            .endif

                        .elseifs ( edx < 0 )

                            or  flags,FL_NEGATIVE
                        .endif
                    .endif
                    ;
                    ; check precision value for default; non-default
                    ; turns off 0 flag, according to ANSI.
                    ;
                    .ifs ( precision < 0 )
                        mov precision,1 ; default precision
                    .else
                        and flags,NOT FL_LEADZERO
                    .endif
                    ;
                    ; Check if data is 0; if so, turn off hex prefix
                    ;
                    .if ( !eax && !edx )
                        mov prefixlen,eax
                    .endif
                    ;
                    ; Convert data to ASCII -- note if precision is zero
                    ; and number is zero, we get no digits at all.
                    ;
                    .if ( flags & FL_SIGNED )

                        test edx,edx
                        .ifs
                            neg eax
                            neg edx
                            sbb edx,0
                            or  flags,FL_NEGATIVE
                        .endif
                    .endif

                    lea rbx,buffer[BUFFERSIZE-1]
ifdef _WIN64
                    mov r8,rbx
                    mov r9d,curadix
                    shl rdx,32
                    or  rax,rdx

                    .fors ( : rax || precision > 0 : precision-- )

                        xor edx,edx
                        div r9
                        add dl,'0'
                        .ifs dl > '9'
                            add dl,byte ptr hexoff
                        .endif
                        mov [rbx],dl
                        dec rbx
                    .endf

else

                    .fors ( : eax || edx || precision > 0 : precision-- )

                        .if ( !edx || !curadix )

                            div curadix
                            mov ecx,edx
                            xor edx,edx

                        .else

                            push esi
                            push edi

                            .for ( ecx = 64, esi = 0, edi = 0 : ecx : ecx-- )

                                add eax,eax
                                adc edx,edx
                                adc esi,esi
                                adc edi,edi

                                .if ( edi || esi >= curadix )

                                    sub esi,curadix
                                    sbb edi,0
                                    inc eax
                                .endif
                            .endf
                            mov ecx,esi
                            pop edi
                            pop esi
                        .endif

                        add ecx,'0'
                        .ifs ( ecx > '9' )
                            add ecx,hexoff
                        .endif
                        mov [ebx],cl
                        dec ebx
                    .endf

endif
                    ; compute length of number

                    lea rax,buffer[BUFFERSIZE-1]
                    sub rax,rbx
                    add rbx,1

                    ; text points to first digit now

                    ; Force a leading zero if FORCEOCTAL flag set

                    .if ( flags & FL_FORCEOCTAL )

                        .if ( byte ptr [rbx] != '0' || eax == 0 )

                            dec rbx
                            mov byte ptr [rbx],'0'
                            inc eax
                        .endif
                    .endif
                    mov text,rbx
                    mov textlen,eax
                .endsw
                ;
                ; At this point, we have done the specific conversion, and
                ; 'text' points to text to print; 'textlen' is length.   Now we
                ; justify it, put on prefixes, leading zeros, and then
                ; print it.
                ;
                .if ( !no_output )

                    .if ( flags & FL_SIGNED )
                        .if ( flags & FL_NEGATIVE )
                            ; prefix is a '-'
                            mov prefix,'-'
                            mov prefixlen,1
                        .elseif ( flags & FL_SIGN )
                            ; prefix is '+'
                            mov prefix,'+'
                            mov prefixlen,1
                        .elseif ( flags & FL_SIGNSP )
                            ; prefix is ' '
                            mov prefix,' '
                            mov prefixlen,1
                        .endif
                    .endif
                    ;
                    ; calculate amount of padding -- might be negative,
                    ; but this will just mean zero
                    ;
                    mov eax,fldwidth
                    sub eax,textlen
                    sub eax,prefixlen
                    mov padding,eax
                    ;
                    ; put out the padding, prefix, and text, in the correct order
                    ;
                    .if ( !( flags & ( FL_LEFT or FL_LEADZERO ) ) )
                        ;
                        ; pad on left with blanks
                        ;
                        write_multi_char( ' ', padding, fp, &charsout )
                    .endif
                    ;
                    ; write prefix
                    ;
                    write_string( &prefix, prefixlen, fp, &charsout )

                    .if ( ( flags & FL_LEADZERO ) && !( flags & FL_LEFT ) )
                        ;
                        ; write leading zeros
                        ;
                        write_multi_char( '0', padding, fp, &charsout )
                    .endif

                    ; write text
ifdef __UNIX__
                    write_string( text, textlen, fp, &charsout )
else
                    .if ( bufferiswide && textlen )

                        mov rbx,text
                        .while textlen

                            .break .ifd !WideCharToMultiByte( 0, 0, rbx, 1, &mbuf, 1, 0, 0 )

                            movzx ecx,mbuf
                            write_char( ecx, fp, &charsout )

                            add rbx,2
                            sub textlen,2
                           .break .ifs
                        .endw
                    .else
                        write_string( text, textlen, fp, &charsout )
                    .endif
endif

                    .if ( flags & FL_LEFT )

                        ; pad on right with blanks

                        write_multi_char( ' ', padding, fp, &charsout )
                    .endif
                .endif
                ;
                ; we're done!
                ;
                .endc
            .endsw
        .endif
    .endw
    .return( charsout ) ; return value = number of characters written

_output endp

    end
