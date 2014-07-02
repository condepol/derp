rm -f dhcp-pre.txt dns-pre.txt text.txt dns.txt dhcp.txt analysis.txt

for i in `find $1 -type f -name \*.cap `;
do
  echo $i ;
  ls -rthl $i ;
  # 802.11
  # probes
  tshark \
  -e "wlan_mgt.ssid" \
  -e "bootp.option.vendor_class_id" \
  -e "bootp.option.domain_name" \
  -e "bootp.option.hostname"  \
  -e "dhcpv6.vendorclass.data"  \
  -e "dhcpv6.domain"            \
  -e "dns.qry.name" \
  -e "dns.ptr.domain_name" \
  -e "dns.resp.name" \
  -e "text" \
  -Tfields -Eoccurrence=a -Equote=n -r $i >> analysis.txt;
done;

cat analysis.txt | awk -F "\t" '{print $1}' | sort -u >> ssids.txt
cat analysis.txt | awk -F "\t" '{print $2}' | tr ',' '\n' | sort -u >> dhcp-pre.txt
cat analysis.txt | awk -F "\t" '{print $3}' | tr ',' '\n' | sort -u >> dhcp-pre.txt
cat analysis.txt | awk -F "\t" '{print $4}' | tr ',' '\n' | sort -u >> dhcp-pre.txt
cat analysis.txt | awk -F "\t" '{print $5}' | tr ',' '\n' | sort -u >> dhcp-pre.txt
cat analysis.txt | awk -F "\t" '{print $6}' | tr ',' '\n' | sort -u >> dhcp-pre.txt
cat analysis.txt | awk -F "\t" '{print $7}' | tr ',' '\n' | sort -u >> dns-pre.txt
cat analysis.txt | awk -F "\t" '{print $8}' | tr ',' '\n' | sort -u >> dns-pre.txt
cat analysis.txt | awk -F "\t" '{print $9}' | tr ',' '\n' | sort -u >> dns-pre.txt
cat analysis.txt | awk -F "\t" '{print $10}' | tr ',' '\n' | sort -u >> text.txt

cat dhcp-pre.txt | sort -u > dhcp.txt
cat dns-pre.txt  | sort -u > dns.txt

cat dns.txt ssids.txt text.txt | sed -e 's/$/  /g' | grep -v '\(HTTP request\|HTML\|Timestamps\)' |tr -d '\n' | less

