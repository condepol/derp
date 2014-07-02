import struct as s;
print("".join(["944626378ace9bdf"[int(i,16)]for i in"".join([s.pack(">I",1+s.unpack(">I","08863B053A41"[-8:].decode('hex'))[0]).encode('hex')[int(u)]for u in"51274063"])]));
