.name "stayin' alive"
.comment "Ha, Ha, Ha, stayiiiiin' aliiiiiiiiiive"

		sti       r1, %69, %1
		sti       r1, %34, %1
		ld        %1, r3
		ld        %33, r6
		add       r2, r3, r2
		xor       r2, %15, r4
		live      %4
		zjmp      %16
		fork      %-21
		ld        %0, r4
		zjmp      %-31
		ld        %0, r4
		live      %4
		zjmp      %-5
