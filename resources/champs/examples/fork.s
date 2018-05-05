.name "zork"
.comment ""

start:	ld %43581439, r4
		ld %4294902272, r5
		sti r4, %:start, %-8
		sti r5, %:start, %-4
		and r8, r8, r8
		zjmp %-100
