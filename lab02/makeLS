my_ls: my_ls.o
	gcc -o my_ls my_ls.o

my_ls.o: my_ls.c
	gcc -c -Wall my_ls.c

install: my_ls
	mkdir ./bin/
	mv ./my_ls ./bin/my_ls

clean:
	rm my_ls.o

distclean: clean
	rm -R ./bin/
