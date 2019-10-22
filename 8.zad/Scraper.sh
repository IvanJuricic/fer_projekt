#! /bin/bash
da="DA"
ne="NE"
echo "Zelite li preuzeti naslove sa pocetne stranice Njuskala?(DA/NE)"
read input
if [ "$input" == "$da" ];
then  echo "https://www.njuskalo.hr/gradnja-iskopi" |
   wget -O- -i- | 
   hxnormalize -x | 
   hxselect -i article h3 |  
   lynx -stdin -dump > nesto.txt;
   cat nesto.txt
fi
