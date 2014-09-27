import json,sys,socket as S
h,p=sys.argv[1:]
p=int(p)
u,K,L='utf8',bytes,len
s=S.socket(2,1);s.connect((h,p))
def z():
 a,b=0,s.recv(1)[0]
 while b&128:a,b=(a<<7)+b&127,s.recv(1)[0]
 return b&127+(a<<7)
def V(d,b):return K([(64*(i!=b//7))+((d>>(7*(i)))%128)for i in range(1+b//7)])
def D(d):return V(L(d),L(d).bit_length())+d
s.send(D(K(2)+D(K(h,u))+K([p>>8,p%256,1]))+K([1,0]))
z()
z()
l,d=z(),K()
while L(d)<l:d+=s.recv(1024)
s.close()
print(json.loads(str(d,u)))
