.name "Ez"
.comment "Only win"
		
#create:	fork %:jump
		
#write:	sti	r1,%:live,%1
#		and	%0 ,%0,r2

#live:	live	%1
#		zjmp	%:live

jump:	ldi %:load, %0, r3
		ldi %:load, %4, r4
		ldi %:load, %8, r5
		ldi %:load, %12, r6
		ldi %:load, %16, r7
		ldi %:load, %20, r8

load:	live %1
		sti r3, %128, %0
		sti r4, %125, %0
		sti r5, %122, %0
		sti r6, %119, %0
		sti r7, %116, %0
		sti r8, %113, %0
		and %0 , %0 , r15
		sti r1, %:liver, %1

liver:	live %1

