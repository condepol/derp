D=256
l,i,b=D*[0],D*[0],1
for L in range(D):
 l[b],i[L],b=L,b,b<<1
 if b>255:b^=285
l[1]=0
def p(b):
 r=1
 for z in range(b):r=i[(l[r]+l[214])%D];
 return r
print[p(z) for z in range(D)]
