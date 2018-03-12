/*Written by Liam O'Brien & Taner Doganay*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node* insert();

struct Node {
    char* string;
    struct Node *next;
};

int main ( int argc, char *argv[] ) {
	if (argv[1]) {
		char *input = (char*)malloc(strlen(argv[1]));
		struct Node * head;
		strcpy(input, argv[1]);
		int stringStart = -1;
		for (int i = 0; i <= strlen(input); i++) {
			if (isalpha(input[i]) && stringStart == -1) {
				stringStart = i;
			} else if (!(isalpha(input[i])) && stringStart != -1) {
				char *word = (char*)malloc(strlen(input));
				strncpy(word, (input + stringStart), (i - stringStart));
				head = insert(word, head);
				stringStart = -1;
			}
		}
		struct Node * nodePtr = malloc(sizeof(struct Node));
		for (nodePtr = head; nodePtr != NULL; nodePtr = nodePtr->next) {
			printf("%s\n", nodePtr->string);
		}
	} else {
		printf("%s\n", "error");
	}
}

struct Node* insert ( char *word, struct Node * head ) {
	struct Node * newNode = malloc(sizeof(struct Node));
	newNode->string = word;
	newNode->next = NULL;
	if (head == NULL) {
		head = newNode;
		return head;
	} else {
		struct Node * nodePtr = malloc(sizeof(struct Node));
		struct Node * nodePtrPrev = malloc(sizeof(struct Node));
		for (nodePtr = head; nodePtr != NULL; nodePtr = nodePtr->next) {
			if (strcmp(nodePtr->string, word) > 0 && nodePtr == head) {
				newNode->next = nodePtr;
				head = newNode;
				return head;
			} else if (strcmp(nodePtr->string, word) > 0 && strcmp(nodePtrPrev->string, word) <= 0) {
				newNode->next = nodePtr;
				nodePtrPrev->next = newNode;
				return head;
			} else if (strcmp(nodePtr->string, word) < 0 && nodePtr->next == NULL){
				nodePtr->next = newNode;
				return head;
			} else if (strcmp(nodePtr->string, word) < 0 && strcmp(nodePtr->next->string, word) >= 0) {
				newNode->next = nodePtr->next;
				nodePtr->next = newNode;
				return head;
			} else if (strcmp(nodePtr->string, word) < 0 && nodePtr == head && strcmp(nodePtr->next->string, word) >= 0) {
				newNode->next = head->next;
				head->next = newNode;
				return head;
			}
			nodePtrPrev = nodePtr;
		}
	}
	return head;
}