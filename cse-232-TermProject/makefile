all: myeditor

clean:
	rm -rf *.o

functions.o: functions.c
	gcc -c functions.c

main.o: main.c
	gcc -c main.c

myeditor: functions.o main.o
	gcc functions.o main.o -o myeditor -lncurses
