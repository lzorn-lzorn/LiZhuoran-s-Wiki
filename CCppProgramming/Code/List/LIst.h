#ifndef LIST_H
#define LIST_H
typedef enum Result{
	FAIL = 0,
	SUCCESS = 1
}Result;

typedef struct List{
	struct List* next;
	int value;
}List;

Result InitList(List** list);
void DestroyList(List** list);
#endif