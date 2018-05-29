.name "Croustibat"
.comment "Qui peut le battre? - Findus"

		live      %1
		fork      %70
		fork      %35
		ldi       %56, %0, r2
		ld        %-84, r3
		ld        %0, r12
		zjmp      %35
		live      %1
		zjmp      %3
		ldi       %24, %4, r2
		ld        %-80, r3
		ld        %0, r12
		zjmp      %3
		sti       r2, r3, r4
		zjmp      %-89
		live      %1
		fork      %28
		ld        %-410, r4
		ld        %0, r12
		fork      %-62
		live      %1
		zjmp      %-94
		fork      %33
		ld        %-390, r4
		ld        %0, r12
		live      %1
		fork      %-95
		live      %1
		zjmp      %-127
		live      %1
		fork      %24
		sti       r1, %141, %1
		sti       r12, %-7, %1
		sti       r12, %-163, %5
		live      %1
		fork      %35
		live      %1
		fork      %59
		ldi       %104, %0, r2
		ld        %11, r3
		ld        %0, r12
		zjmp      %83
		live      %1
		fork      %51
		ldi       %72, %4, r2
		ld        %15, r3
		ld        %0, r12
		zjmp      %51
		ldi       %48, %8, r2
		ld        %19, r3
		ld        %0, r12
		zjmp      %27
		ldi       %24, %12, r2
		ld        %23, r3
		ld        %0, r12
		zjmp      %3
		live      %1
		sti       r2, r3, r4
		sti       r12, r3, %487
