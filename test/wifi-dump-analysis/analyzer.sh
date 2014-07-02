#!/bin/bash
echo "analysis of $1"
for i in `find $1 -type f -name \*.cap `;
do
  echo $i ;
  ls -rthl $i ;
  echo  802.11
  echo  probes
  tshark -Y "wlan.fc.type_subtype eq 4" -e "wlan_mgt.ssid" -Tfields -Eoccurrence=a -Equote=n -r $i | sort -u | grep -v ^$ >>  $1/probes.txt ;
  echo  beacons
  tshark -Y "wlan.fc.type_subtype eq 8" -e "wlan_mgt.ssid" -Tfields -Eoccurrence=a -Equote=n -r $i | sort -u | grep -v ^$ >>  $1/beacons.txt;

  echo  HTTP
  tshark -Y "http" -e "http.request.full_uri" -Tfields -Eoccurrence=a -Equote=n -r $i | sort -u | grep -v ^$ >>  $1/uris.txt
  tshark -Y "http" -e "http.user_agent"       -Tfields -Eoccurrence=a -Equote=n -r $i | sort -u | grep -v ^$ >>  $1/UAs.txt
  echo  DHCP
  tshark -Y "bootp" -e "bootp.option.hostname"        -Tfields -Eoccurrence=a -Equote=n -r $i | sort -u | grep -v ^$ >>  $1/dhcp-hostnames.txt;
  tshark -Y "bootp" -e "bootp.option.vendor_class_id" -Tfields -Eoccurrence=a -Equote=n -r $i | sort -u | grep -v ^$ >>  $1/dhcp-vendor_class_id.txt;
  tshark -Y "bootp" -e "bootp.option.domain_name"     -Tfields -Eoccurrence=a -Equote=n -r $i | sort -u | grep -v ^$ >>  $1/dhcp-domain_names.txt;

  echo  DHCPv6 
  tshark -Y "dhcpv6" -e "dhcpv6.vendorclass.data"     -Tfields -Eoccurrence=a -Equote=n -r $i | sort -u | grep -v ^$ >>  $1/dhcpv6-vendor_class.txt;
  tshark -Y "dhcpv6" -e "dhcpv6.domain"               -Tfields -Eoccurrence=a -Equote=n -r $i | sort -u | grep -v ^$ >>  $1/dhcpv6-domain_names.txt;

  echo  DNS
  tshark -Y "dns" -e "dns.qry.name"                   -Tfields -Eoccurrence=a -Equote=n -r $i | tr ',' '\n' | sort -u | grep -v ^$ >>  $1/dns-query-names.txt;
  tshark -Y "dns" -e "dns.ptr.domain_name"            -Tfields -Eoccurrence=a -Equote=n -r $i | tr ',' '\n' | sort -u | grep -v ^$ >>  $1/dns-ptr-domains.txt;
  tshark -Y "dns" -e "dns.resp.name"                  -Tfields -Eoccurrence=a -Equote=n -r $i | tr ',' '\n' | sort -u | grep -v ^$ >>  $1/dns-resp-names.txt;

  echo  Net Bios
  tshark -Y "nbns"  -e "text"                 -Tfields -Eoccurrence=a -Equote=n -r $i | tr ',' '\n' | sort -u | grep -v ^$ >>  $1/netbios-names.txt;
  tshark -Y "nbdgm" -e "text"                 -Tfields -Eoccurrence=a -Equote=n -r $i | tr ',' '\n' | sort -u | grep -v ^$ >>  $1/netbios-names.txt;
  tshark -Y "smb"   -e "text"                 -Tfields -Eoccurrence=a -Equote=n -r $i | tr ',' '\n' | sort -u | grep -v ^$ >>  $1/netbios-names.txt;

done

cat $1/dns-* | tr ',' '\n'     | sort -u > $1/dns.txt
cat $1/probes.txt $1/beacons.txt  | sort -u > $1/ssids.txt
cat $1/dhcp-* $1/dhcpv6-*         | sort -u > $1/dhcp.txt

