for (( i = 0; i < 10000000; i++)) do
	echo $i
	./gen $i >01
	./triangles <01
done
