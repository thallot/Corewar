.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, 11, %:live
		and r1, %0, r6

live:	live %1
		fork %12
		zjmp %:live
