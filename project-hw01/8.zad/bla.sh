echo "https://www.njuskalo.hr/audio-video-foto" |
   wget -O- -i- | 
   hxnormalize -x | 
   hxselect -i article h3 |  
   lynx -stdin -dump > nesto.txtThis file found
