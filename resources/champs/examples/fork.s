.name "zork"
.comment ""

start:	fork %-150
		and %0, %0, r3
		zjmp %:start
