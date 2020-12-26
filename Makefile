drc : obj/domino.o obj/main.o obj/debugger.o
	g++ -o drc obj/domino.o obj/main.o obj/debugger.o -pthread

obj/domino.o :
	g++ -c src/domino.cpp -I headers -o obj/domino.o

obj/main.o : 
	g++ -c src/main.cpp  -I headers -o obj/main.o

obj/debugger.o :
	g++ -c src/debugger.cpp  -I headers -o obj/debugger.o

clean:
	rm -frv obj
	mkdir obj
	rm -f drc

run: drc
	./drc