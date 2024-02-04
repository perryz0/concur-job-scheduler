OPTS = -g -Wall -std=c11

all: count_typos

count_typos: count_typos.o Utils.o SpellChecker.o
	gcc $(OPTS) -o $@ $^

count_typos.o: count_typos.c
	gcc $(OPTS) -o $@ -c $<

Utils.o: Utils.c Utils.h
	gcc $(OPTS) -o $@ -c $<

SpellChecker.o: SpellChecker.c
	gcc $(OPTS) -o $@ -c $<

clean:
	rm -f count_typos *.o
