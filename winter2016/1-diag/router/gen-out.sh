#!/bin/bash

for ((i=1;i<=8;++i)); do
	cp 00$i router.in
	./router <router.in >router.out || (echo "RE on test $i" && continue)
	mv router.out 00$i.out
	echo "Generated answer for test $i"
done
zip routeranswers.zip ???.out
