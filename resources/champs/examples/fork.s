.name "zork"
.comment ""

		ld %1, r1
		sti r1, %:begin, %42

begin:	and 42, %255, r2
		st r2, 10
