# C'est le premier script que j'ai fait.
# Il m'a servi a identifier les noms de champs et filtres à utiliser.
# À ne pas utiliser
for i in `find $1 -type f -name \*.cap `;
do
  echo $i ;
  ls -rthl $i ;
  # 802.11
  # probes
  tshark -Y "wlan.fc.type_subtype eq 4" -e "wlan_mgt.ssid" -Tfields -Eoccurrence=a -Equote=n -r $i >> probes.txt ;
  # beacons
  tshark -Y "wlan.fc.type_subtype eq 8" -e "wlan_mgt.ssid" -Tfields -Eoccurrence=a -Equote=n -r $i >> beacons.txt;

  # HTTP
  tshark -T "http" -e "http.request.full_uri" -Tfields -Eoccurrence=a -Equote=n -r $i >> uris.txt
  tshark -T "http" -e "http.user_agent"       -Tfields -Eoccurrence=a -Equote=n -r $i >> UAs.txt
  # DHCP
  tshark -Y "bootp" -e "bootp.option.hostname"        -Tfields -Eoccurrence=a -Equote=n -r $i >> dhcp-hostnames.txt;
  tshark -Y "bootp" -e "bootp.option.vendor_class_id" -Tfields -Eoccurrence=a -Equote=n -r $i >> dhcp-vendor_class_id.txt;
  tshark -Y "bootp" -e "bootp.option.domain_name"     -Tfields -Eoccurrence=a -Equote=n -r $i >> dhcp-domain_names.txt;

  # DHCPv6 
  tshark -Y "dhcpv6" -e "dhcpv6.vendorclass.data"     -Tfields -Eoccurrence=a -Equote=n -r $i >> dhcpv6-vendor_class.txt;
  tshark -Y "dhcpv6" -e "dhcpv6.domain"               -Tfields -Eoccurrence=a -Equote=n -r $i >> dhcpv6-domain_names.txt;

  # DNS
  tshark -Y "dns" -e "dns.qry.name"                   -Tfields -Eoccurrence=a -Equote=n -r $i >> dns-query-names.txt;
  tshark -Y "dns" -e "dns.ptr.domain_name"            -Tfields -Eoccurrence=a -Equote=n -r $i >> dns-ptr-domains.txt;
  tshark -Y "dns" -e "dns.resp.name"                  -Tfields -Eoccurrence=a -Equote=n -r $i >> dns-resp-names.txt;

  # Net Bios
  tshark -Y "nbns"  -e "text"                 -Tfields -Eoccurrence=a -Equote=n -r $i >> netbios-names.txt;
  tshark -Y "nbdgm" -e "text"                 -Tfields -Eoccurrence=a -Equote=n -r $i >> netbios-names.txt;
  tshark -Y "smb"   -e "text"                 -Tfields -Eoccurrence=a -Equote=n -r $i >> netbios-names.txt;


done

cat dns-* | tr ',' '\n'     | sort -u > dns.txt
cat probes.txt beacons.txt  | sort -u > ssids.txt
cat dhcp-* dhcpv6-*         | sort -u > dhcp.txt
