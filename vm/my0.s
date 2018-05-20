.name "zork"
.comment ""

		ld %6, r3
		ld :missile, r2
		and r12, r12 ,r12
launcher:	live %1
		fork %:start
		zjmp %:launcher

start:	live %1
generator:	fork %:missile
		zjmp %:start

missile: sti r2, r3, %0
