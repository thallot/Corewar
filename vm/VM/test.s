.name		"Champotte"
.comment	"Jour J"

#		ld	5, r2
		ld	42,r3
#		xor %5, r1, r4
#		and r5,r5,r5
		label: live %1
#		zjmp %:label
#		live %:label
#		and %:label, r1, r4
#		ld	%-10,r3
#		sub r1, r6, r3
#		add r1, r1, r6
#		st	r1, 6
#		st	r1, r3
#		live %:label
#	ld   %0, r14			# $A -6 -0
