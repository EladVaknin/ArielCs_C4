#ifndef TRIE_H_
#define TRIE_H_
#define NUM_LETTERS 26
typedef struct node node;
typedef enum 
{
	FALSE = 0, TRUE = 1
} boolean;
extern node *trie;
node* init();
boolean insert(char*);
void printTrie(boolean);
void readWords();
void printTree(node*, char*, int);
void killTree(node*);
void printTreeR(node*, char*, int);
#endif 
