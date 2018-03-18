.name "zork"
.comment "I'M ALIIIIVE"

l1:		st r1, r2
		or %0, %16, r3
		or %0, %16, r4

l2:		sti r2, %:live, %1
		and r1, %0, r1

live:	live %1
		sti r2, r3, r4
		add r3, r4, r4
		and r1, %0, r1
		zjmp %:live
