; Example assembly language program -- modified
; Author:  David Thompson modifying code authored by R. Detmer
; Date:   10/2/16
; 

.586
.MODEL FLAT

.STACK  4096            ; reserve 4096-byte stack

.DATA                   ; reserve storage for data
number  DWORD   -105    ; a dowrd location labeled "number" contains a value of -105
x		DWORD   16      ; a dowrd location labeled "x" contains a value of 16
y		DWORD   -16     ; a dowrd location labeled "y" contains a value of -16
z		DWORD   32      ; a dowrd location labeled "z" contains a value of 32
sum     DWORD   ?       ; a dword location "sum" with contents undefined

.CODE                           ; start of main program code
main    PROC        
	mov     eax, number			; contents of "number" to EAX
      		add     eax, 158        ; add 158
		add		eax, x			; add x
		add		eax, y			; add y
    	mov     sum, eax				; sum in eax is trasfered to memory at "sum"
	mov     eax,z					; contents of "z" to EAX
		add		eax, sum		; add previous sum to EAX
	mov     sum, eax				; sum in eax is trasfered to memory at "sum"
	mov		eax, 0				; exit with return code 0
        ret						
main    ENDP

END	                             ; end of source code
