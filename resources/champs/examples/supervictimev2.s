.name "victime"
.comment "
laisse-moi gagner stp
allez soit sympa
mon code est tout pourri
je suis pacifiste
tu n'auras aucune satisfaction à me vaincre
inversement te vaincre sera le succès de ma vie
on ne doit pas frapper les handicapés
ne soit pas une vilaine personne
j'ai des lunettes
la violence ne résout rien
essayons de trouver un compromis
il y a assez de gloire pour tout le monde
pète un coup ça va te détendre
il y a déjà suffisamment de violence dans le monde
allez viens boire un café
concentrons nos efforts dans l'amélioration
toutes les vies sont précieuses
ensemble construisons un monde meilleur
concentrons nous sur le positifs de la vie
ne fait pas betement ce qu'on te demande"


# r2 contenus missile down
# r3 part missile * 4
# r4 const 40 (ou le missile est ecrit)
# r5 const 0
# r6 num missile
# r7 contenus missile up
# r8 const -56 (ou le missile est ecrit)

			xor		r2, r2, r2
sup:		zjmp	%:start
			zjmp	%0

# lance missile up

lnch4:
			sti		r7, r3, %-24
			zjmp	%-27
lnch5:
			sti		r7, r3, %-49
			zjmp	%-52
lnch6:
			sti		r7, r3, %-74
			zjmp	%-77

# init value

start:		
			ld		%40, r4
			ld		%-56, r8
			sti		r5, %:sup, %1
			sti		r1, %:strcreap, %1
			sti		r1, %:lvfrkp1, %1
			sti		r1, %:lvfrkp2, %1
			sti		r1, %:lvemsl, %1
			sti		r1, %:lvemsl2, %1
			sti		r1, %:strcrea, %1
			sti		r1, %:mslup, %1
			sti		r1, %:mslup12, %1
			sti		r1, %:mslup3str, %1
			sti		r1, %:msldown, %1
			sti		r1, %:msldown12, %1
			sti		r1, %:msldown3str, %1
			sti		r1, %:pmsl, %1

# crea missile
			ld		%0, r5
strcrea:	
			live	%42
			fork	%:msldown
mslup:		
			live	%42
			fork	%:mslup3str
mslup12:	
			live	%42
			fork	%:mslup2
mslup1:
			ld		%3, r6
			ld		%0, r5
			zjmp	%:strcreap
mslup2:
			ld		%4, r6
			ld		%0, r5
			zjmp	%:strcreap
mslup3str:	
			live	%42
			fork	%:mslupstr
mslup3:
			ld		%5, r6
			ld		%0, r5
			zjmp	%:strcreap
mslupstr:
			zjmp	%:strcrea

#########################################################################

msldown:	
			live	%42
			fork	%:msldown3str

msldown12:	
			live	%42
			fork	%:msldown2

msldown1:
			ld		%0, r6
			ld		%0, r5
			zjmp	%:strcreap

msldown2:
			ld		%1, r6
			ld		%0, r5
			zjmp	%:strcreap

msldown3str:	live	%42
			fork	%:msldownstr

msldown1:
			ld		%2, r6
			ld		%0, r5
			zjmp	%:strcreap

msldownstr:
			fork	%:strcrea
			zjmp	%:strcrea

# crea part missile

strcreap:	live	%42
			fork	%:lvfrkp2
lvfrkp1:	live	%42
			fork	%:jmpfrkp1
			ld		%4, r3
			ld		%0, r5
			zjmp	%:pmsl
jmpfrkp1:	ld		%0, r3
			ld		%0, r5
			zjmp	%:pmsl
lvfrkp2:	live	%42
			fork	%:jmpfrkp2
			ld		%12, r3
			ld		%0, r5
			zjmp	%:pmsl
jmpfrkp2:	ld		%8, r3
			ld		%0, r5
			zjmp	%:pmsl

# missile exemple

srtmsl:		zjmp	%0
lvemsl:		live	%42
			sti		r2, r3, r4
			zjmp	%38

# missile exemple 2

srtmsl2:	zjmp	%0
lvemsl2:	live	%42
			sti		r7, r3, r8
			zjmp	%-58

# init missile

pmsl:		live	%42
			fork	%:pmsl
			ldi		%:srtmsl, r3 ,r2
			ldi		%:srtmsl2, r3 ,r7
# charge missile

			xor		r6, %0, r5
			zjmp	%:lnch1
			xor		r6, %1, r5
			zjmp	%:lnch2
			xor		r6, %2, r5
			zjmp	%:lnch3
			xor		r6, %3, r5
			zjmp	%:lnch4
			xor		r6, %4, r5
			zjmp	%:lnch5
			ld 		%0, r5
			zjmp	%:lnch6

# lance missile down

lnch1:
		#zjmp	%0
		sti		r2, r3, %43
		zjmp	%40
lnch2:
		#zjmp	%0
		sti		r2, r3, %50
		zjmp	%47
lnch3:
		#zjmp	%0
		sti		r2, r3, %9
		zjmp	%6
