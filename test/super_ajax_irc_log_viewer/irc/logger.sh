#!/bin/bash
bot_name="qolund_ii_log"
server="irc.freenode.net"
channel="#naohack"
logfile="naohack.log"

ii -i ii -s ${server} -n ${bot_name} &
sleep 5
echo "/j ${channel}" > ii/${server}/in
chmod a+rx ii
chmod a+rx ii/${server}
chmod a+rx ii/${server}/${channel}
chmod a+r ii/${server}/${channel}/out
