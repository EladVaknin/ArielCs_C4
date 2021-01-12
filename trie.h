#ifndef TRIE_H_
#define TRIE_H_
#define NUM_LETTERS 26
typedef struct node node;
typedef enum {
	FALSE = 0, TRUE = 1
} boolean;
extern node *trie;
node* init();
boolean insert(char*);
void readWords();
void killTree(node*);
void printTrie(boolean);
void printTree(node*, char*, int);
void printTreeR(node*, char*, int);
#endif /* TRIE_H_ */