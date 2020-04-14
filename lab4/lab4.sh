rm f1.txt
for ((c=1; c<=512; c++))
do
    echo "$c" | ./lab4 -f1 | tee -a f1.txt
done

rm f2.txt
for ((c=1; c<=4000000000; c=c*2))
do
    echo "$c" | ./lab4 -f2 | tee -a f2.txt
done