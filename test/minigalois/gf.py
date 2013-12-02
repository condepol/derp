import sys
e=256
l,i,b,r=e*[0],e*[0],1,1
for L in range(e):
 l[b],i[L],b=L,b,b<<1
 if b>255:b^=285
l[1]=0
for z in range(e):
 sys.stdout.write(chr(r))
 r=i[(l[r]+l[214])%e]
