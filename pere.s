.name "POUR MON PERE ET SON PERE AVANT LUI"
.comment "Ce champion n'est pas un champion, c'est l'interpretation du sacrifice de generation pour le bien de la descendance familiale. Privilegiant la survie de son espece, avant la survie personnelle."
protection: zjmp %-50
            zjmp %-50
            zjmp %-50
            zjmp %-50
            zjmp %-50
            zjmp %-50
            zjmp %-50
            zjmp %-50
setup:      ld %0, r2
            ld %1, r3
            ld %4, r4
            ld %5, r5
            sti r1, %:alive, %1
alive:      live %1
			add r2, r3, r2
            add r5, r4, r5
            sti r2, r5, %0
birth:      fork %:alive




