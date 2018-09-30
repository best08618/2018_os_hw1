OBJECTS = main_fun.o fork.o full.o path.o print.o SiSH.o token.o

shell : $(OBJECTS)
	gcc -o shell $(OBJECTS) -lpthread

main.o: main_fun.c
	gcc -c main_fun.c -lpthread
full.o: full.c
	gcc -c full.c -lpthread
path.o: path.c
	gcc -c path.c -lpthread
fork.o: fork.c
	gcc -c fork.c -lpthread
print.o: print.c
	gcc -c print.c -lpthread
SiSH.o: SiSH.c
	gcc -c SiSH.c -lpthread
token.o: token.c
	gcc -c token.c -lpthread
clean:
	rm -rf shell




