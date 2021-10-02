c_code=18098_project2.c
all : a.out

a.out : $(c_code)
	gcc $(c_code) -Wall

clean:
	rm -f a.out txt createLongCSV.c longCSV gmon.out test 

testall:
	gcc $(c_code) -Wall -pg
	bash automaticTests.sh
	echo ""
	gprof a.out gmon.out > txt
	echo ""
	head -n 30 txt

upload:
	scp automaticTests.sh 18098_project2.c samplev1 testBoth.sh Makefile timeToRunBoth.sh e18098@aiken.ce.pdn.ac.lk:~/co222/project2/