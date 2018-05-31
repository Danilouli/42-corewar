.name "Croustibat"
.comment "Qui peut le battre? - Findus"

#r2 -> code

setup:		live %0
erase:		ld %0, r12
			ldi %:change, %2, r12
			sti r12, %:erase, %2
			zjmp %:virus
			ld %0, r12
			zjmp %:wipe

virus:		ld %420, r14
			fork %:2a

1a:
			ld %1, r13
			ldi %:tremplin, %0, r2
			ldi %:tremplin2, %0, r3
			ldi %:corrupt, %0, r4
			ldi %:corrupt2, %0, r5
			ldi %:corrupt3, %0, r6
			ldi %:corrupt4, %0, r7
			ldi %:backoff, %0, r8
			ldi %:backoff2, %0, r9
			ldi %:backoff3, %0, r10
			ldi %:backoff4, %0, r11
			ld %86, r15
			ld %0, r12
			zjmp %:jump

change:		ld %1, r12

2a:
			ld %0, r13
			ldi %:tremplin, %4, r2
			ldi %:tremplin2, %4, r3
			ldi %:corrupt, %4, r4
			ldi %:corrupt2, %4, r5
			ldi %:corrupt3, %4, r6
			ldi %:corrupt4, %4, r7
			ldi %:backoff, %4, r8
			ldi %:backoff2, %4, r9
			ldi %:backoff3, %4, r10
			ldi %:backoff4, %4, r11
			ld %90, r15
			ld %0, r12
			zjmp %:jump

wipe:		live %1
erase2:		sti r1, %:balai, %1
			and r13, r13, r13
			zjmp %:2b

1b:			fork %:3b
			ldi %:balai, %0, r2
			ld %11, r3
			ld %0, r12
			zjmp %:balai

2b:			fork %:4b
			ldi %:balai, %4, r2
			ld %15, r3
			ld %0, r12
			zjmp %:balai

3b:			ldi %:balai, %8, r2
			ld %19, r3
			ld %0, r12
			zjmp %:balai

4b:			ldi %:balai, %12, r2
			ld %23, r3
			ld %0, r12
			zjmp %:balai


tremplin:	sti r3, r15, r14
			zjmp %500

tremplin2:	sti r4, r15, r14
			zjmp %500

corrupt:	sti r5, r15, r16
			zjmp %81

corrupt2:	sti r6, r15, r16
			zjmp %81

corrupt3:	sti r7, r15, r16
			zjmp %81

corrupt4:	sti r8, r15, r16
			zjmp %81

backoff:	sti r9, r15, r14
			zjmp %500

backoff2:	sti r10, r15, r14
			zjmp %500

backoff3:	sti r11, r15, r14
			zjmp %500

backoff4:	sti r12, r15, r14
			zjmp %500

jump:		sti r2, r15, r14
			zjmp %476

balai:		live %1
			sti r2, r3, r16
			sti r16, r14, r15
