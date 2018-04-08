.name "test"
.comment "AU STERONE"

start:		live		%42
			ld			123, r1
#			ld			%321, r1
			st			r1, %:start   # met dans r1
			add			r1, r2, r3
			sub			r1, r2, r3
			and			123, %321, r1 #oui
			or			%321, 123, r1
			xor			123, %321, r1

			#mettre un label ici # vraiment

			zjump		%:start
			ldi			%321, r1, r2
			sti			r1, r2, r3
			fork		%:aff
#mouai
			lld			%321, r1
			lldi		123, %321, r1
			lfork		%:start
aff:		aff			r1
			and			r1, r2, r3
			and			123, r2, r3
			and			%321, r2, r3
			and			r1, 2123, r3
			and			123, 2123, r3
			and			%321, 2123, r3
			and			r1, %2321, r3
			and			123, %2321, r3
			and			%321, %2321, r3

#			add			r1, r2, r3
#			add			123, r2, r3
#			add			%321, r2, r3
#			add			r1, 2123, r3
#			add			123, 2123, r3
#			add			%321, 2123, r3
#			add			r1, %2321, r3
#			add			123, %2321, r3
#			add			%321, %2321, r3
#			add			r1, r2, 3123
#			add			123, r2, 3123
#			add			%321, r2, 3123
#			add			r1, 2123, 3123
#			add			123, 2123, 3123
#			add			%321, 2123, 3123
#			add			r1, %2321, 3123
#			add			123, %2321, 3123
#			add			%321, %2321, 3123
#			add			r1, r2, %3321
#			add			123, r2, %3321
#			add			%321, r2, %3321
#			add			r1, 2123, %3321
#			add			123, 2123, %3321
#			add			%321, 2123, %3321
#			add			r1, %2321, %3321
#			add			123, %2321, %3321
#			add			%321, %2321, %3321
