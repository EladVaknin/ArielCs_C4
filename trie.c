#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	long unsigned int count;
	struct node *children[NUM_LETTERS];
} node;
node *trie;
struct node* init() {	//init empty node
	node *numOfNode = NULL;
	numOfNode = (node*) malloc(sizeof(node));	//allocate size for node struct
	if (numOfNode != NULL) {
		numOfNode->letter = '\0';
		numOfNode->count = 0;
		for (int i = 0; i < NUM_LETTERS; i++)	//init the childrens
			numOfNode->children[i] = NULL;
	}
	return numOfNode;
}
boolean insert(char *word) {
	node *PointNode = trie;	//set pointer to the root
	int counter = 0, index = 0;
	while (word[counter] != '\0') {
		index = word[counter] - 'a';	//convert alphabet index to array index
		if (index < 0 || index >= NUM_LETTERS) {//char not small alphabet, check if upper case alphabet
			index += 'a' - 'A';	//if a capital letter, add ascii value and convert index
			word[counter] += 'a' - 'A';
			if (index < 0 || index >= NUM_LETTERS) {
				counter++;	//check the next char
				continue;	//ignore non small alphabet characters
			}
		}
		if (PointNode->children[index] == NULL) {//if char doesn't exist - create new node and set letter
			PointNode->children[index] = init();
			if (PointNode->children[index] == NULL)
				return FALSE;	//fail to allocate memory
			PointNode->children[index]->letter = word[counter];
		}
		PointNode = PointNode->children[index];	// move to the next child and check the next char
		counter++;
	}
	PointNode->count++;	//new word -> add to count

	return TRUE;
}
void readWords() {
	char *word = NULL; //pointer to word
	char *temp = NULL; //temporare pointer
	int i = 0;
	int size = 1;
	word = (char*) malloc(1); //init input size of one char
	if (scanf("%c", &word[i]) != 1) {
		free(word);
		return;
	}
	while (word[i] != EOF) {
		size++;		//more chars in STDIN - increase size of string
		temp = (char*) realloc(word, size + 1); //reallocate space
		if (temp == NULL) {	//try to reallocate into new space
			free(word);
			return;
		}
		word = temp;
		i++;	//next index for char input
		if (scanf("%c", &word[i]) != 1) {
			free(word);
			return;
		}
		if (word[i] == ' ' || word[i] == '\n') {
			word[i] = '\0';	//set end of word
			if (insert(word) == FALSE) {	//add word to tree
				printf("failed to add the word %s to trie", word);
				free(word);
				return;
			}
			free(word);	//free memory of the last word
			size = 1;
			i = 0;	//set index and size for new word
			word = (char*) malloc(1);	//allocate memory for new word
			if (scanf("%c", &word[i]) != 1) {
				free(word);
				return;
			}
		}

	}

}

void killTree(node *root) { //free memory of tree
	if (root != NULL) {
		for (int i = 0; i < NUM_LETTERS; i++)	//free children first
			killTree(root->children[i]);
		free(root);
	}

}
void printTrie(boolean r) {
	char *word = NULL;
	word = (char*) malloc(2);	//allocate space for first char and end of word
	if (r == FALSE) {	//print lexicographically
		for (int i = 0; i < NUM_LETTERS; i++)
			printTree(trie->children[i], word, 2);
	} else {
		for (int i = NUM_LETTERS - 1; i >= 0; i--)	//print reverse order
			printTreeR(trie->children[i], word, 2);
	}
	free(word);

}
void printTree(node *PointNode, char *word, int size) {
	char *temp = NULL;
	if (PointNode == NULL)
		return;
	word[size - 2] = PointNode->letter;	//add current char to string and end word
	word[size - 1] = '\0';
	if (PointNode->count > 0)	//node is end of word, print word

		printf("%s\t%ld\n", word, PointNode->count);

	size++;
	temp = malloc(size);	//prepare string for next children
	if (temp == NULL)
		return;
	for (int i = 0; i < size - 1; i++)//deep copy of string, prevent memory conflicts
		temp[i] = word[i];
	for (int i = 0; i < NUM_LETTERS; i++)	//recursive call lexico order

		printTree(PointNode->children[i], temp, size);

	free(temp);	//finished with all sons of node, can release this string
}

void printTreeR(node *PointNode, char *word, int size) {
	char *temp = NULL;
	if (PointNode == NULL)	//check if node empty - nothing to print
		return;
	word[size - 2] = PointNode->letter;	//add current char to string and end word
	word[size - 1] = '\0';
	size++;
	temp = malloc(size);	//prepare string for next children
	if (temp == NULL)
		return;
	for (int i = 0; i < size - 1; i++)	//copy string and send to children
		temp[i] = word[i];

	for (int i = NUM_LETTERS - 1; i >= 0; i--)	//recursive call reverse lexico

		printTreeR(PointNode->children[i], temp, size);

	free(temp);	//finished with children - release copied string

	if (PointNode->count > 0)	//if word ending - print word
		printf("%s\t%ld\n", word, PointNode->count);

}