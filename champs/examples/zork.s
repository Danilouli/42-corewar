.name "zork"
.comment "I'M ALIIIIVE"

coco:	st r1, r2
		st r2, r3
		sti r2, r1, %12
		and %0, %0, r5
		zjmp %:coco
