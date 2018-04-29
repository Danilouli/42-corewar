.name "test"
.comment "kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill"

		add	r2,r2,r2
		sti	 r1, %:lu, %1
		sti	 r1, %:li, %1
		ldi 0, %:loop, r2
		zjmp %:zero
loop:	zjmp %0
		zjmp %0
zero:	fork %:li

lu:		live %42
un:		fork %:end
		sti	r2, 0, %:deux
		zjmp %:end
li:		live %42
deux:	lfork %:end
end:
