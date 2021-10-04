c_code=18098_project2.c

a.out : $(c_code)
	gcc $(c_code) -Wall

clean:
	rm -f a.out txt createLongCSV.c longCSV gmon.out test 

testall:
	gcc $(c_code) -Wall
	bash automaticTests.sh $(l)

upload:
	scp automaticTests.sh $(c_code) samplev1 testBoth.sh Makefile timeToRunBoth.sh e18098@aiken.ce.pdn.ac.lk:~/co222/project2/

rungprof:
	gcc $(c_code) -Wall -pg
	bash automaticTests.sh $(l)
	gprof a.out gmon.out > txt
	head -n 30 txt