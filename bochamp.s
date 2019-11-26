.name "Bochamp"
.comment "Salut, ca wol?"

            sti r1, %:live, %1

live:       live %1

fork %:live

lld 

live %1