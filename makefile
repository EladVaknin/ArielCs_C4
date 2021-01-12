CC=gcc
AR=ar
OBJECTS_MAIN=main.o
OBJECTS_TRIE=trie.o
FLAGS= -Wall -g

all: libTrie.a frequency
frequency: $(OBJECTS_MAIN) libTrie.a
	$(CC) $(FLAGS) -o frequency $(OBJECTS_MAIN) libTrie.a
libTrie.a: $(OBJECTS_TRIE)
	$(AR) -rcs libTrie.a $(OBJECTS_TRIE)
trie.o: trie.c trie.h
	$(CC) $(FLAGS) -c trie.c
main.o: main.c trie.h
	$(CC) $(FLAGS) -c main.c 

.PHONY: clean all

clean:
	rm -f *.o *.a *.so frequency