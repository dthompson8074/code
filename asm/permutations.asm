; Programmming Project 2: using modified runtime i/o file
;David Thompson

.586
.MODEL FLAT
EXTRN _printf:PROC
EXTRN _scanf:PROC
.STACK  4096            ; reserve 4096-byte stack

.DATA                   ; reserve storage for data
n		DWORD	5 DUP (?)
k		DWORD	5 DUP (?)
perm     DWORD   ?
msg	db  	"Enter n:", 10, 0
msg2	db  	"Enter k:", 10, 0
format1	db	"%d", 0  	
format2	db  "permutations = %d", 10, 0

.CODE                           ; start of main program code
main    PROC        
	
	;initialization
	mov esi, offset k
	mov eax, 0
	mov perm, 1

	;prompt for k: use printf(msg2)
	pusha					; restore all registers
	push offset msg2			;single parameter
	call _printf
	add esp, 4				; restore top of the stack
	popa					;restore all registers
	
	;input: use scanf("%d, &k)
	pusha				;push all registers
	push esi			;first parameter: address x
	push offset format1		;second parameter: format string
	call _scanf
	add esp, 8
	popa				;restore all registers

	add eax, dword ptr [esi]	 	;move k to eax
	dec eax					;k- 1
	mov ecx, eax				;set loop count to k-1    
	add esi, 4				;advance source index
	mov eax, 0				;reset eax

	;prompt for n: use printf(msg)
	pusha					; restore all registers
	push offset msg			;single parameter
	call _printf
	add esp, 4				; restore top of the stack
	popa					;restore all registers
	
	;input: use scanf("%d, &n)
	pusha				;push all registers
	push esi			;first parameter: address x
	push offset format1		;second parameter: format string
	call _scanf
	add esp, 8
	popa					;restore all registers

	add eax, dword ptr [esi]		; n to eax  
	mov ebx, eax				;n to ebx	
	dec ebx					;ebx = (n-1)

cmp ecx,0 

jz	_else_if				;edge case (k = 1)
jl _else					;edge case (k = 0)


	next:
	
	;permuation computation loops (k-1) times
	
    	mul ebx					;n(n-i)	
	dec ebx;				;(n-i+1)

	loop next
	
	mov perm, eax         ; perm to memory

jmp _endif

_else_if:
	mov perm, eax         ; perm to memory
jmp _endif


_else:
	mov perm,1;

_endif:

	
	;output: use printf("perm = %d", perm)
	push perm				; first paramenter address perm 
	push offset format2		; second parameter: format string
	call _printf
	add esp, 8				; restore top of the stack
	ret 0	

main    ENDP

END	                             ; end of source code
