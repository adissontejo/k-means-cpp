#!/usr/bin/env python3

import sys
from random import randint as ri
from random import choice as cc

if len(sys.argv) < 2:
    print('   *** Usage: %s <N> [k]' % sys.argv[0] )
    exit(0)

N=int(sys.argv[1])
k=3 if len(sys.argv) < 3 else int(sys.argv[2])

print(N, 2)

K=[ (ri(100,500), ri(100,500)) ]
while len(K) < k:
	x, y = ri(100,500), ri(100, 500)
	
	ok=True
	for p in K:
		px, py = p
		if (x-px)*(x-px)+(y-py)*(y-py) < 200:
			ok=False

	if ok:
		K.append( (x,y) )

P=[]

while len(P) < N:
	tx,ty=cc(K)

	x,y = tx + ri(-100,100), ty+ri(-100,100)

	P.append( (x,y) )
	print(x,y)


print(k)







