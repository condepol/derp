import os,socket as z,struct as S,time
P,i=print,os.getpid()&65535
for H in ['heise.de','localhost','127.0.0.2','127.4.5.6','2.2.2.2']:
 try:
  s=z.socket(2,3,1)
  s.settimeout(0.2)
  H,head,data=z.gethostbyname(H),S.pack("bbHHh",8,0,0,i,1),S.pack("d",time.time())+bytes([81]*68)
  head=S.pack("bbHHh",8,0,S.unpack('<H',S.pack('>H',65535^((lambda x:(x%65536)+(x>>16))(sum(S.unpack('H',(head+data)[i:i+2])[0]for i in range(0,len((head+data)),2))))))[0],i,1)
  s.sendto(head+data,(H,1))
  p,a=s.recvfrom(1024)
  P("{:9s} : \x1b[32mup\x1b[0m {:0.4f}ms".format(H,time.time()-S.unpack("d",p[28:28+S.calcsize("d")])[0]))
  s.close()
 except z.gaierror as e:
  P("{:9s} : \x1b[31munresolvable\x1b[0m :{}".format(H,e))
 except z.timeout as e:
  P("{:9s} : \x1b[31mdown\x1b[0m".format(H))

