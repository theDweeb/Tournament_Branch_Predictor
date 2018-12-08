

all:
	g++ -std=c++14 main.cpp bimodal.cpp global.cpp gshare.cpp tll.cpp GSelect.cpp GSelect.h main.h bimodal.h global.h gshare.h tll.h -o tournament
	

main:

clean:
	-rm tournament
	
