python3 -c 'import sys,math;[1 for i in range(2000) if sys.stdout.write("{}\x1b[3{};4{}m{}\x1b[0m\n".format(" "*int(1+90*math.sin(i*i/2)),i%9,int(i*0.2)%7,i)) == sys.stdout.flush()];'
