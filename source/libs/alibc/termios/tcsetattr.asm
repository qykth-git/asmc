; TCSETATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include linux/kernel.inc
include termios.inc

    .code

tcsetattr proc fd:int_t, cmd:int_t, termios_p:ptr termios

    .ifs ( edi < 0 )

        _set_errno(EBADF)
        .return -1
    .endif
    .if ( rdx == NULL )

        _set_errno(EINVAL)
        .return -1
    .endif

    .switch (esi)
    .case TCSANOW
      mov esi,TCSETS
     .endc
    .case TCSADRAIN
      mov esi,TCSETSW
     .endc
    .case TCSAFLUSH
      mov esi,TCSETSF
     .endc
    .default
      _set_errno(EINVAL)
     .return -1
    .endsw

    .ifsd ( sys_ioctl(edi, esi, rdx) < 0 )

        neg eax
        _set_errno(eax)
        .return -1
    .endif
    ret

tcsetattr endp

    end