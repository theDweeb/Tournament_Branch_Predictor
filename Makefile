

all:
	g++ -std=c++14 main.cpp gshare.cpp tll.cpp main.h gshare.h tll.h -o tournament
	

main:

clean:
	-rm tournament
	
