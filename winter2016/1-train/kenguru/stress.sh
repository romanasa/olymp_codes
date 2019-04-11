
for (( i = 0; i < 10000000; i++ ))
do
	./gen %i >01
	./kenguru <01 >02
	./kenguru_slow <01 >03

	echo $i
	diff 02 03 || break

	echo ok
done

