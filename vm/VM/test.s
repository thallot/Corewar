.name		"Champotte"
.comment	"Jour J"

#		ld	5, r2
#		ld	42,r3
#		xor %5, r1, r4
		and r5,r5,r5
		label: live %1
		zjmp %42
		zjmp %:label
#		live %:label
#		and %:label, r1, r4
#		ld	%-10,r3
<<<<<<< HEAD
#		sub r1, r6, r3
#		add r1, r1, r6
#		st	r1, 6
#		st	r1, r3
#		live %:label
=======
#	sub r1, r6, r3
#	add r1, r6, r6
#		ld	%851958,r3
		st	r1, 6
#		st	r1, r3
		live %96
		fork %-10
>>>>>>> adda90614e635b7cb4c1f42188affa3836db537c
#	ld   %0, r14			# $A -6 -0
