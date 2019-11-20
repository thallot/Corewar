.name		"Champotte"
.comment	"Jour J"

#	live:	st r1, 6
#		live %4
#fork %-10
#		xor r2, r3, r9
#		xor %3, 15, r3
#		xor r2, r3, r9
#		xor	r3, %10, r3
#		zjmp %:live
#		ldi %295, %390, r1
#		lldi %295, %390, r1
		ld	655, r2
		lld	655,r3
#ld	%0,r3
#		xor %5, r1, r4
#		and r5,r5,r5
#		label: live %1
#		zjmp %42
#		zjmp %:label
#		live %:label
#		and %:label, r1, r4
#		ld	%-10,r3
#		sub r1, r6, r3
#		add r1, r1, r6
#		st	r1, 6
#		st	r1, r3
#		live %:label
#	sub r1, r6, r3
#	add r1, r6, r6
#		ld	%851958,r3
#	st	r1, 6
#		st	r1, r3
#		live %96
#		fork %-10
#	ld   %0, r14			# $A -6 -0
