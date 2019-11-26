.name "Ez"
.comment "Only win"
		
create:	fork %:jump
		
write:	sti	r1,%:live,%1
		and	%0 ,%0,r2

live:	live	%1
		zjmp	%:live

jump:	live %1
		and %0, %0, r2
		sti r1, %:create, %1

