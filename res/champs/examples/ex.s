.name "zork"
.comment "I'M ALIIIIVE"

		ld		%102, r7				; r7 = 102
		ld		%128, r8				; r8 = 128
		sti		r1, %:live, %1			; Assigne le livecode et live
		ld		%4, r3					; r3 = 4

loop:	add		r2, r3, r2				; r2 = r3 + r2
		ldi		%:loop, r6, r5			; r5 = contenu présent à l'adresse (loop + r6)
		xor		r2, %68, r4				; Sort du loop
		zjmp	%:end					; Jump to end
		sti		r5, r7, r2				; Copie le contenu de r5 dans l'adresse à (r7 + r2)
		add		r6, r3, r6				; r6 = r3 + r6
		ld		%0, r4					; r4 = 0

live:	live	%1						; Live
		zjmp	%:loop					; Saute à loop

end:	ld		%0, r2					; r2 = 0
		ld		%0, r6					; r6 = 0
		fork	%0
