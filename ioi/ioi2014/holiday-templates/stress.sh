for (( i=0; i < 100000; i++ ))
do
	echo $i
	./gen $i >01
	./holidayok <01 >02
	./holiday <01 >03
	diff 02 03 || break
done
