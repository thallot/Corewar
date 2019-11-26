.name "Ez"
.comment "Only win"
		
create:	fork %:jump
		
write:	sti	r1,%:live,%1
		and	%0 ,%0,r2

live:	live	%1
		zjmp	%:live

writer: and %8, %8, r2
		sti r2, %:loin, r2

jump:	live %1
		and 	%0, %0, r2
		sti		r1, %:live, %1
		zjmp 	%:create

loin:	
