$b=1;foreach(0..255){$l[$b]=$_;$i[$_]=$b;$b<<=1;$b^=285if$b>255;};$l[1]=0;$r=1;foreach(@l){print chr($r);$r=$i[($l[$r]+$l[214])%256];}
