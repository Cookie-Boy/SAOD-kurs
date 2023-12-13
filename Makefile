all: compile link

compile:
	g++ -Isrc -c src/utils.cpp -o obj/utils.o
	g++ -Isrc -c src/sorting.cpp -o obj/sorting.o
	g++ -Isrc -c src/queue.cpp -o obj/queue.o
	g++ -Isrc -c src/tree.cpp -o obj/tree.o
	g++ -Isrc -c src/encoding.cpp -o obj/encoding.o
	g++ -Isrc -c src/main.cpp -o obj/main.o

link:
	g++ obj/utils.o obj/sorting.o obj/queue.o obj/tree.o obj/encoding.o obj/main.o -o bin/main.exe

clean:
	del /Q /F obj/utils.o
	del /Q /F obj/sorting.o
	del /Q /F obj/queue.o
	del /Q /F obj/tree.o
	del /Q /F obj/encoding.o
	del /Q /F obj/main.o
	del /Q /F bin/main.exe

run:
	./bin/main.exe