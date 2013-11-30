int l[256],i[256],b=1,j=0;p(c){int r=1;while(c--){r=i[(l[r]+l[214])%256];}return r;}main(){while(j<256){l[b]=j;i[j]=b;b<<=1;b=(b>255)?b^285:b;j++;}l[1]=0;while(j--){putchar(p(j));}}
