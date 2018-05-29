.name "Barriere"
.comment "Envoie des torpilles a l'avant et se protege avec des barrieres a l'avant et a l'arriere"

		and       r6, %0, r6
		zjmp      %301
		ld        %-5, r5
		ld        %1024, r4
		ld        %-5, r3
		live      %42
		sti       r4, %-26, r3
		add       r3, r5, r3
		sti       r4, %-37, r3
		add       r3, r5, r3
		sti       r4, %-48, r3
		add       r3, r5, r3
		sti       r4, %-59, r3
		add       r3, r5, r3
		sti       r4, %-70, r3
		add       r3, r5, r3
		xor       r3, %-430, r15
		zjmp      %-75
		and       r6, %0, r6
		zjmp      %-79
		live      %42
		fork      %-108
		zjmp      %-8
		live      %42
		sti       r1, %259, r9
		sti       r1, %263, r9
		sti       r1, %267, r9
		sti       r1, %271, r9
		sti       r1, %275, r9
		sti       r1, %279, r9
		sti       r1, %283, r9
		sti       r1, %287, r9
		sti       r1, %291, r9
		sti       r1, %295, r9
		sti       r1, %299, r9
		sti       r1, %303, r9
		sti       r1, %307, r9
		sti       r1, %311, r9
		sti       r1, %315, r9
		sti       r1, %319, r9
		sti       r1, %323, r9
		sti       r1, %327, r9
		sti       r1, %331, r9
		sti       r1, %335, r9
		sti       r1, %339, r9
		sti       r1, %343, r9
		sti       r1, %347, r9
		sti       r1, %351, r9
		sti       r1, %355, r9
		xor       r9, %6, r10
		zjmp      %77
		ld        %6, r9
		and       r6, %0, r6
		zjmp      %-181
		fork      %450
		live      %42
		sti       r1, %-285, %1
		fork      %-210
		live      %42
		sti       r1, %342, %1
		fork      %303
		live      %42
		ld        %1, r9
		and       r6, %0, r6
		zjmp      %-237
		live      %42
		fork      %19
		live      %42
		fork      %-13
		live      %42
		zjmp      %-21
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		live      %42
		zjmp      %-245
		live      %42
		fork      %6
		zjmp      %-8
		ld        %-5, r5
		ld        %12, r4
		ld        %10, r3
		live      %1
		sti       r4, %77, r3
		sub       r3, r5, r3
		sti       r4, %66, r3
		sub       r3, r5, r3
		sti       r4, %55, r3
		sub       r3, r5, r3
		sti       r4, %44, r3
		sub       r3, r5, r3
		sti       r4, %33, r3
		sub       r3, r5, r3
		xor       r3, %435, r15
		zjmp      %-75
		and       r6, %0, r6
		zjmp      %-79
		zjmp      %-82
		live      %42
		fork      %44
		live      %42
		fork      %77
		live      %42
		fork      %140
		ld        %12, r2
		ld        %192, r5
		and       r6, %0, r6
		zjmp      %190
		live      %42
		fork      %74
		live      %42
		fork      %149
		ld        %0, r2
		ld        %180, r5
		and       r6, %0, r6
		zjmp      %149
		live      %42
		fork      %91
		live      %42
		ld        %8, r2
		ld        %188, r5
		and       r6, %0, r6
		zjmp      %111
		live      %42
		fork      %-503
		ld        %4, r2
		ld        %184, r5
		and       r6, %0, r6
		zjmp      %78
		ld        %16, r2
		ld        %196, r5
		and       r6, %0, r6
		zjmp      %53
		ld        %20, r2
		ld        %200, r5
		and       r6, %0, r6
		zjmp      %28
		ld        %24, r2
		ld        %204, r5
		and       r6, %0, r6
		zjmp      %3
		ldi       %0, r2, r3
		sti       r3, r5, %19
		live      %42
		and       r6, %0, r6
		zjmp      %180
