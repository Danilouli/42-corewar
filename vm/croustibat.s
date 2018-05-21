.name "Croustibat"
.comment "Qui peut le battre? - Findus"

#r2 -> code

virus:		live %1
			fork %:duplicate
			fork %:2b

1b:			ldi %:corrupt, %0, r2
			ld %-84, r3
			ld %0, r12
			zjmp %:corrupt

late:		live %1
			zjmp %:2b
2b:			ldi %:corrupt, %4, r2
			ld %-80, r3
			ld %0, r12
			zjmp %:corrupt

corrupt:	sti r2, r3, r4
			zjmp %-89

duplicate:	live %1
			fork %:duplicate2
			ld %-410, r4
			ld %0, r12
			fork %:late
			live %1
			zjmp %:1b

duplicate2:	fork %:wipe
			ld %-390, r4
			ld %0, r12
			live %1
			fork %:late
			live %1
			zjmp %:1b

wipe:		live %1
			fork %:second
erase:		sti r1, %:balai, %1
			sti r12, %:erase, %1
			sti r12, %:virus, %5
second:		live %1
			fork %:2c

1c:			live %1
			fork %:3c
			ldi %:balai, %0, r2
			ld %11, r3
			ld %0, r12
			zjmp %:balai

2c:			live %1
			fork %:4c
			ldi %:balai, %4, r2
			ld %15, r3
			ld %0, r12
			zjmp %:balai

3c:			ldi %:balai, %8, r2
			ld %19, r3
			ld %0, r12
			zjmp %:balai

4c:			ldi %:balai, %12, r2
			ld %23, r3
			ld %0, r12
			zjmp %:balai

balai:	live %1
		sti r2, r3, r4
		sti r12, r3, %487
