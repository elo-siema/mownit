rm wyniki.txt
for c in {10, 100, 200, 400, 500, 600, 700, 800, 900, 1000}
do
    ./lab6 $c | tee -a wyniki.txt
done
