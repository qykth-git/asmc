.pragma list(push, 0)

DISPID_READYSTATE       equ (-525)
DISPID_READYSTATECHANGE equ (-609)
DISPID_AMBIENT_TRANSFERPRIORITY equ (-728)
DISPID_AMBIENT_OFFLINEIFNOTCONNECTED equ (-5501)
DISPID_AMBIENT_SILENT   equ (-5502)
ifndef DISPID_AMBIENT_CODEPAGE
DISPID_AMBIENT_CODEPAGE equ (-725)
DISPID_AMBIENT_CHARSET  equ (-727)
endif

.pragma list(pop)