for ((i=0; i<100000; i++))
do
	./gen $i >01
	./gameok <01 >02
	./game <01 >03
	echo $i
	diff 02 03 || break
done
