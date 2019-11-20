.name           "Champotte"
.comment        "Jour J"

#               ld      5, r2
#               ld      %0,r3
#               xor %5, r1, r4
                un: live %1
				deux: live %8
				ldi %:deux, %1, r2
				sti r2, %:un, %1
				xor :un, %2, r3
#               zjmp %:label
#               zjmp %42
#               live %:label
#               and %:label, r1, r4
#               ld      %-10,r3
#               sub r1, r6, r3
#               add r1, r1, r6
#               st      r1, 6
#               st      r1, r3
#               live %:label
#       ld   %0, r14                    # $A -6 -0
