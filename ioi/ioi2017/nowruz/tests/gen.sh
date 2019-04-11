for (( i = 0; i < 10; i++ ))
do
	echo $i
	./nowruz $2 <0$i.in >0$i.out
done
./nowruz $2 <10.in >10.out

zip answers$1.zip ??.out
