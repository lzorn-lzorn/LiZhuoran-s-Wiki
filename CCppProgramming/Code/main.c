#include <stdio.h>
#include <stdlib.h>
#include "List/List.h"
int main() {
	printf("Hello, World!\n");
	List* myList = NULL;
	if (InitList(&myList) == SUCCESS) {
		printf("List initialized successfully.\n");
	} else {
		printf("Failed to initialize list.\n");
	}
	DestroyList(&myList);
	system("pause"); 
	return 0;
}