.name       "helltrain"
.comment    "choo-choo, motherf*****s !"
    add     r2,r2,r2

entry:
    zjmp    %:deux
		zjmp    %:un
		zjmp    %:sept
		zjmp    %:un
    zjmp    %:deux
		zjmp    %:sept

un:
sept:
deux:
    zjmp    %:entry

sept:
deux:
		live %1
		zjmp		%:deux
		zjmp    %:sept

trois:
		live %1
		zjmp		%:un
		zjmp		%:deux
		zjmp    %:sept
		zjmp		%:ukuku
		zjmp		%:akaka
		zjmp		%:akaka
ukuku:
akaka:
