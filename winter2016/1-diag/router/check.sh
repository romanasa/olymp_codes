#!/bin/bash

scores=(0 0 4 5 6 6 26 30 23)
total=0
for ((i=1;i<=8;++i)); do
	cp 00$i router.in
	cp 00$i.out router.out
	out=$(./verif_contestant ${scores[$i]})
	echo $out
	score=$(echo $out | awk '{print $1;}')
	total=$((total+score))
done
echo "Total score: $total"
