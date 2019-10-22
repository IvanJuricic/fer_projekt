#! /bin/bash
min=60
echo "Unesite nakon koliko minuta zelite provjeriti tko je ulogiran na ovo racunalo: "
read value
echo $min
echo $value
slp=$(($min*$value)) 
while true; do
    who >> log_history.log
    sleep $slp
done