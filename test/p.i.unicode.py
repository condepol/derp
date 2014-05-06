import sys,time,random
p,x="\x1b[0G\x1b[34m⨊\x1b[31m",sys.stdout
def a(s,*z):x.write(p+s.format(*z));x.flush();time.sleep(.02)
while 1:
 t=random.choice("⛩⚢⚣⚥⚤⚦⚧〠⛪⛫☪☫☬☭☮☯⚜⭓🗼🗽😸🙆🚁🏯🏭🏰👬👫👭👯👸☨☧☦☥✠✡✝⛟✈⛇⛄☻☺☕⛵")
 for i in range(25):a(i*" "+"➠"+(24-i)*" "+"\x1b[32m{}",t)
 a("{:>26s}\n","💥")
