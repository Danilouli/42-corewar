.name "sandwich"
.comment "kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill bill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill kill
kill kill kill kill kill kill kill kill kill kill kill"


		add        r2,r2,r2
nop:	zjmp	%:true

_loop:  zjmp    %0
_good:	add     r2, r3, r2
        ldi        %:_loop, r6, r5
        xor        r2, %72, r4
        zjmp    %:_end
        sti        r5, r8, r2
        add        r6, r3, r6
        ld        %0, r4
_live:   live    %1
        zjmp    %:_good
_end:    ld        %0, r2
        ld        %0, r6
        zjmp    %-305
        zjmp    %0
        zjmp    %0
        zjmp    %0
        zjmp    %0
        zjmp    %0
        zjmp    %0

_loop2:  zjmp    %0
_good2:	add     r2, r3, r2
        ldi        %:_loop2, r6, r5
        xor        r2, %72, r4
        zjmp    %:_end2
        sti        r5, r8, r2
        add        r6, r3, r6
        ld        %0, r4
_live2:   live    %1
        zjmp    %:_good2
_end2:    ld        %0, r2
        ld        %0, r6
        zjmp    %-305
        zjmp    %0
        zjmp    %0
        zjmp    %0
        zjmp    %0
        zjmp    %0
        zjmp    %0

_loop3:  zjmp    %0
_good3:	add     r2, r3, r2
        ldi        %:_loop3  , r6, r5
        xor        r2, %72, r4
        zjmp    %:_end3
        sti        r5, r8, r2
        add        r6, r3, r6
        ld        %0, r4
_live3:   live    %1
        zjmp    %:_good3
_end3:    ld        %0, r2
        ld        %0, r6
        zjmp    %-305

 jump:  sti     r1, %:live, %1
        sti     r1, %:live2, %1
        sti     r1, %:live3, %1
        sti     r1, %:_live, %1
        sti     r1, %:_live2, %1
        sti     r1, %:_live3, %1
true:   sti     r1, %:l, %1
        sti     r1, %:a, %1
        sti     r1, %:b, %1
        sti     r1, %:c, %1
        sti     r1, %:d, %1
        sti     r1, %:e, %1
        sti     r1, %:h, %1
        ld        %222 , r7
        ld        %-272 , r8
        ld        %4, r3
        ld        %0, r2
	    ld        %0, r6

l:		live	%1
		fork	%:l
h:		live	%1
		fork	%:e
        zjmp    %:d
e:		live	%1
		fork	%:c
        zjmp    %:jump
c:		live	%1
		fork	%:good2
        zjmp    %:good3
d:		live	%1
		fork	%:b
        zjmp    %:a
a:		live	%1
		fork	%:_good
        zjmp    %:_good2
b:		live	%1
		fork	%:_good3
        zjmp    %:good1

loop:   zjmp    %0
good1:	add     r2, r3, r2
        ldi        %:loop, r6, r5
        xor        r2, %72, r4
        zjmp    %:end
        sti        r5, r7, r2
        add        r6, r3, r6
        ld        %0, r4
live:   live    %1
        zjmp    %:good1
end:    ld        %0, r2
        ld        %0, r6
        zjmp    %190
        zjmp    %0
        zjmp    %0
        zjmp    %0
        zjmp    %0
        zjmp    %0
        zjmp    %0

loop2:   zjmp    %0
good2:	add     r2, r3, r2
        ldi        %:loop2, r6, r5
        xor        r2, %72, r4
        zjmp    %:end2
        sti        r5, r7, r2
        add        r6, r3, r6
        ld        %0, r4
live2:   live    %1
        zjmp    %:good2
end2:    ld        %0, r2
        ld        %0, r6
        zjmp    %190
        zjmp    %0
        zjmp    %0
        zjmp    %0
        zjmp    %0
        zjmp    %0
        zjmp    %0

loop3:   zjmp    %0
good3:	add     r2, r3, r2
        ldi        %:loop3, r6, r5
        xor        r2, %72, r4
        zjmp    %:end3
        sti        r5, r7, r2
        add        r6, r3, r6
        ld        %0, r4
live3:   live    %1
        zjmp    %:good3
end3:    ld        %0, r2
        ld        %0, r6
        zjmp    %190
