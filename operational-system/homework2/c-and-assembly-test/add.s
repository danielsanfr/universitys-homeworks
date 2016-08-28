; make the add function visible to the linker
global add

; int __cdecl add(int a, int B)/>
; adds two integers and returns the result
add:
    mov eax, [esp+4] ; get the 2nd parameter off the stack
    mov edx, [esp+8] ; get the 1st parameter off the stack
    add eax, edx ; add the parameters, return value in eax
    ret ; return from sub-routine
