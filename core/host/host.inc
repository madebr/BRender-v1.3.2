
	include pretok.inc

host_regs_x STRUCT
    _edi    dd ?
    _esi    dd ?
    _ebp    dd ?
    _res    dd ?
    _ebx    dd ?
    _edx    dd ?
    _ecx    dd ?
    _eax    dd ?

    flags   dw ?
    _es     dw ?
    _ds     dw ?
    _fs     dw ?
    _gs     dw ?
    _ip     dw ?
    _cs     dw ?
    _sp     dw ?
    _ss     dw ?
host_regs_x ENDS

host_regs_w STRUCT
    _di     dw ?
    _pad0   dw ?
    _si     dw ?
    _pad1   dw ?
    _bp     dw ?
    _pad2   dw ?
    _res    dw ?
    _pad3   dw ?
    _bx     dw ?
    _pad4   dw ?
    _dx     dw ?
    _pad5   dw ?
    _cx     dw ?
    _pad6   dw ?
    _ax     dw ?
    _pad7   dw ?

    flags   dw ?
    _es     dw ?
    _ds     dw ?
    _fs     dw ?
    _gs     dw ?
    _ip     dw ?
    _cs     dw ?
    _sp     dw ?
    _ss     dw ?
host_regs_w ENDS

host_regs_h STRUCT
    _pad0   dd 4 dup (?)
    _bl     db ?
    _bh     db ?
    _pad1   db ?
    _pad2   db ?
    _dl     db ?
    _dh     db ?
    _pad3   db ?
    _pad4   db ?
    _cl     db ?
    _ch     db ?
    _pad5   db ?
    _pad6   db ?
    _al     db ?
    _ah     db ?
    _pad7   db ?
    _pad8   db ?
host_regs_h ENDS

host_regs UNION
    x host_regs_x <>
    w host_regs_w <>
    h host_regs_h <>
host_regs ENDS

BRE_FAIL equ 1002h
BRE_ALLREADY_ACTIVE equ 1007h

HOST_CAPS_PORTS EQU 00000200h
HOST_CAPS_MMX   EQU 00000400h
HOST_CAPS_FPU   EQU 00000800h
HOST_CAPS_CMOV  EQU 00001000h
