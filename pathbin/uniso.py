#!/usr/bin/env python3
# coding: utf-8

import re
import sys
import random
e = ['ascii','big5','big5hkscs','charmap','cp037','cp1006','cp1026','cp1125','cp1140','cp1250','cp1251','cp1252','cp1253','cp1254','cp1255','cp1256','cp1257','cp1258','cp273','cp424','cp437','cp500','cp65001','cp720','cp737','cp775','cp850','cp852','cp855','cp856','cp857','cp858','cp860','cp861','cp862','cp863','cp864','cp865','cp866','cp869','cp874','cp875','cp932','cp949','cp950','euc_jis_2004','euc_jisx0213','euc_jp','euc_kr','gb18030','gb2312','gbk','hp_roman8','hz','idna','iso2022_jp','iso2022_jp_1','iso2022_jp_2','iso2022_jp_2004','iso2022_jp_3','iso2022_jp_ext','iso2022_kr','iso8859_1','iso8859_10','iso8859_11','iso8859_13','iso8859_14','iso8859_15','iso8859_16','iso8859_2','iso8859_3','iso8859_4','iso8859_5','iso8859_6','iso8859_7','iso8859_8','iso8859_9','johab','koi8_r','koi8_u','latin_1','mac_arabic','mac_centeuro','mac_croatian','mac_cyrillic','mac_farsi','mac_greek','mac_iceland','mac_latin2','mac_roman','mac_romanian','mac_turkish','mbcs','palmos','ptcp154','punycode','raw_unicode_escape','rot_13','shift_jis','shift_jis_2004','shift_jisx0213','tis_620','undefined','unicode_escape','unicode_internal','utf_16','utf_16_be','utf_16_le','utf_32','utf_32_be','utf_32_le','utf_7','utf_8','utf_8_sig']

def switch_code(string,a,b):
  try:
    if str(bytes(string,a),b) != string:
      return str(bytes(string,a),b)
  except:
    return None

def recursive_fail(string,level,parents,e):
  if level == 0:
    print("{} > {}".format(parents,string))
    return
  for a in e:
    for b in e:
      if switch_code(string,a,b) is not None:
        recursive_fail(switch_code(string,a,b),level-1,"{} \x1b[33m[\x1b[32m{} \x1b[35m{}\x1b[33m->\x1b[34m{}\x1b[33m«\x1b[0m{}\x1b[33m»]\x1b[0m".format(parents,level,a,b,switch_code(string,a,b)),e)

i = 'utf8'    if len(sys.argv) < 2 else sys.argv[1]
o = 'iso8859' if len(sys.argv) < 3 else sys.argv[2]
s = False     if len(sys.argv) < 4 else sys.argv[3]
if i == 'list': print('\n'.join(e)); sys.exit(0)
if i == 'random': i = random.choice(e);print(i);
if o == 'random': o = random.choice(e);print(o);
if i == 'full':
  try:
    level = int(o)
  except:
    level = 1
  if s:
    if s == 'safe':
      e = [x for x in e if re.search(r'(mac_|iso8|utf_8|ascii)',x)]
  recursive_fail(str(sys.stdin.buffer.read(),'utf8'),level,'',e)
  sys.exit(0)
sys.stdout.write(str(bytes(str(sys.stdin.buffer.read(),'utf8'),i),o))
