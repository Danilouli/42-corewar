.name "zork"
.comment ""

setup:
		live %1
		fork %:duplicate
go:		live %1
		fork %:2b

#r2 -> code

1b:									#23
		ld 40, r2					#7
		ld %-98, r3				#7
		and r12, r12 ,r12			#5
		zjmp %:backfire				#3

2b:									#23
		ld 24, r2
		ld %-94, r3
		and r12, r12 ,r12
		zjmp %:backfire

backfire:	sti r2, r3, r4
jump:		zjmp %-103			#+5

duplicate:	ld %786432, r5
erase1:		sti r1, %:live, %1
erase2:		sti r1, %:launcher, %1
erase3:		sti r1, %:start, %1
			st r12, :erase1
			st r12, :erase2
			st r12, :erase3
			live %1
			fork %:2a

1a:		live %42
		fork %:3a
		ldi %:live, %0, r2
		ld %11, r3			# 0
		and r12, r12 ,r12
		zjmp %:launcher

2a:		live %42
		fork %:4a
		ldi %:live, %4, r2
		ld %15, r3			#+4
		and r12, r12 ,r12
		zjmp %:launcher

3a:		ldi %:live, %8, r2
		ld %19, r3			#+8
		and r12, r12 ,r12
		zjmp %:launcher

4a:		ldi %:live, %12, r2
		ld %23, r3			#+12
		and r12, r12 ,r12
		zjmp %:launcher

launcher:	live %1
		fork %:start
		zjmp %:launcher

start:	live %1
generator:	fork %:missile
		zjmp %:start

live:	live %1				#5
missile: sti r2, r3, r4		#5
attack:	st r5, 510	#5
