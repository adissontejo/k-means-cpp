#!/usr/bin/env python3

import sys
from random import randint as ri
from random import choice as cc

if len(sys.argv) < 3:
    print('   *** Usage: %s <N> <d>' % sys.argv[0] )
    exit(0)

N=int(sys.argv[1])
d=int(sys.argv[2])

MIN, MAX = 0, 10**5

print(N, d)

for i in range(N):
	P=[ str(ri(MIN,MAX)) for j in range(d) ]
	print( ' '.join(P) )


