b=bytes
C=b()
j,z=0,256
S=bytearray(range(z))
for i in S[::]:
 j+=S[i]+(b('ㄙ𐰳ꏒㄊ','utf8')*z)[i]
 S[i],S[j%z]=S[j%z],S[i]
i,j=0,0
for c in b('𐠕𐊸ࡂꨃ','utf8'):
 i=(i+1)%z
 j=(j+S[i])%z
 S[i], S[j] = S[j], S[i]
 C+=b([c^S[(S[i]+S[j])%z]])
