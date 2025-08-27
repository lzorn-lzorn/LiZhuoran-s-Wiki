#include <stdlib.h>
#include "List.h"

Result InitList(List** list){
	*list = (List*)malloc(sizeof(List));
	if (*list){
		(*list)->next = NULL;
		(*list)->value = 0;
		return SUCCESS;
	}
	return FAIL;
}

void DestroyList(List** list){
	List* current = *list;
	while (current) {
		List* next = current->next;
		free(current);
		current = next;
	}
	*list = NULL;
}