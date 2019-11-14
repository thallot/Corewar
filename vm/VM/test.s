.name		"Champotte"
.comment	"Jour J"

#		ld	5, r2
#		ld	%0,r3
#		ld	%-10,r3
	sub r1, r6, r3
	add r1, r6, r6
		st	r1, 6
#		st	r1, r3
		live %96
#	ld   %0, r14			# $A -6 -0
