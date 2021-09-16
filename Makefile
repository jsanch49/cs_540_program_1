all:
	g++ -ldl test.cpp -Wfatal-errors 

clean:
	rm a.out
