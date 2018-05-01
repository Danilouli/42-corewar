.name		"Sliders"
.comment	"And the winner is ..."

	ld 	0, r7
	sti r7, %100, %100

start:	ld %20, r3
	ld %30, r4
	add r4, r3, r5
	add r5, r5, r5
	sub r5, r4, r5
	sti r5, %100, %100
	add r4, r7, r4
	sti r4, %100, %100
