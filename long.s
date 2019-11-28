#by cpoulet, classic imp
#MOD 043: 1879310379-0
#MOD 050: 1879310386-15

.name		"mychicken_fork"
.comment	"one is good, two is better..."

lldi %1024, %1024, r2
lld 2042, r3
ld -10, r4
st r2, 95
st r3, 105
st r4, 105
ld %49, r5
aff r5
add r4, r5, r6
lfork %3097
