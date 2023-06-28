#include "CUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*DATA STRUCTURES*/
/****STACK****/
// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
void stackInit(tStack *s) { s->first = NULL; }

void stackPush(tStack *s, const int elem) {
	tNode *tmp = (tNode*)malloc(sizeof(tNode));
	if (tmp == NULL) { printf("Error allocating memory\n"); }
	else {
		tmp->data = elem;
		tmp->next = s->first;
		s->first = tmp;
	}
}

void stackPop(tStack *s) {
	tNode *tmp = NULL;
	if (s->first == NULL) { printf("Error: stack is empty\n"); }
	else {
		tmp = s->first;
		s->first = tmp->next;
		free(tmp);
	}
}

int stackTop(const tStack s) {
	int elem = 0;
	if (s.first == NULL) {
		printf("Error empty stack\n");
		return -1;
	}
	else { elem = s.first->data; }
	return elem;
}

bool stackEmpty(const tStack s) { return (s.first == NULL); }

//extra
void stackPopN(tStack *s, const int n) {
	tNode *tmp = NULL;
	if (s->first == NULL) { printf("Eror: stack is empty\n"); }
	else {
		int count = 0;
		while (s->first->next != NULL && count < n) {
			tmp = s->first;
			s->first = s->first->next;
			free(tmp);
			count++;
		}
		if (count < n) { printf("Error: stack has less elements than n\n"); }
	}
}

void stackClear(tStack *s) {
	tNode *tmp = NULL;
	if (s->first != NULL) {
		while (s->first != NULL) {
			tmp = s->first;
			s->first = s->first->next;
			free(tmp);
		}
	}
}

/****QUEUE****/
void queueInit(tQueue *q) {
	q->head = NULL;
	q->last = NULL;
}

void enqueue(tQueue *q, const int elem) {
	tNode *tmp = (tNode*)malloc(sizeof(tNode));
	if (tmp == NULL) { printf("Error: failed memory allocation\n"); }
	else {
		tmp->data = elem;
		tmp->next = NULL;
		if (q->head == NULL) { q->head = tmp; }
		else { q->last->next = tmp; }
		q->last = tmp;
	}
}

void dequeue(tQueue *q) {
	tNode *tmp = NULL;
	if (q->head == NULL) { printf("Error: queue is empty\n"); }
	else {
		tmp = q->head;
		q->head = q->head->next;
		if (q->head == NULL) { q->last = NULL; }
		else { free(tmp); }
	}
}

int queueHead(const tQueue q) {
	int elem = 0;
	if (q.head == NULL) {
		printf("Error: stack is empty\n");
		return -1;
	}
	else { elem = q.head->data; }
	return elem;
}

bool queueEmpty(const tQueue q) { return (q.head == NULL); }

//extra
void queueSwapFirst2(tQueue *q) {
	tNode *tmp = NULL;
	if (queueEmpty(*q)) { printf("Error: queue is empty\n"); }
	else {
		if (q->head->next == NULL) { printf("Error: queue must have at least 2 elements\n"); }
		else {
			tmp = q->head;
			q->head = q->head->next;
			tmp->next = tmp->next->next;
			q->head->next = tmp;
		}
	}
}

/****LIST****/
void listInit(tList *l) { l->first = NULL; }

void listInsert(tList *l, const int elem, const int index) {
	tNode *tmp = NULL;
	tNode *prev = NULL;

	if (index == 1) {
		/* no previous element */
		tmp = l->first;
		if (l->first == NULL) { printf("\n Error: empty list\n"); }
		else {
			l->first = tmp->next;
			free(tmp);
		}
	}
	else {
		prev = getNode(l, index - 1);
		if (prev != NULL) {
			/* standard case */
			tmp = prev->next;
			if (tmp == NULL) { printf("\n Error: index position doesn't exist\n"); }
			else {
				prev->next = tmp->next;
				free(tmp);
			}
		}
		else { printf("\n Error: index position doesn't exist\n"); }
	}
}

void listDelete(tList *l, const int index) {
	tNode *tmp = NULL;
	tNode *prev = NULL;

	if (index == 1) {
		/* no previous element */
		tmp = l->first;
		if (l->first == NULL) { printf("\n Error: empty list\n"); }
		else {
			l->first = tmp->next;
			free(tmp);
		}
	}
	else {
		prev = getNode(l, index - 1);
		if (prev != NULL) {
			/* standard case */
			tmp = prev->next;
			if (tmp == NULL) { printf("\n Error: index position doesn't exist\n"); }
			else {
				prev->next = tmp->next;
				free(tmp);
			}
		}
		else { printf("\n Error: index position doesn't exist\n"); }
	}
}

int listGet(tList l, const int index) {
	tNode *curr = getNode(&l, index);
	if (curr == NULL) {
		printf("\n Error: index position doesn't exist\n");
		return -1;
	}
	else { return curr->data; }
}

bool enlistEndd(const tNode *n) { return (n == NULL); }

bool emptyList(const tList l) { return (l.first == NULL); }

/*{auxiliar function}*/
tNode *getNode(const tList *l, const int index) {
	int i = 1;
	tNode *prev = l->first;
	while (i < index && (prev != NULL)) {
		prev = prev->next;
		i++;
	}
	return prev;
}

/*STRING MANIPULATION*/
char *readStringD(const size_t maxSize) {
	if (maxSize < 1) {
		fprintf(stderr, "Size is too small, consider removing parameter for automatic size handling ");
		return NULL;
	}
	else if (maxSize == 1) {
		fprintf(stderr, "Consider using 'readChar();' instead ");
		return NULL;
	}
	else {
		char *buffer = (char*)malloc(sizeof(char) * maxSize);
		gets_s(buffer, maxSize);
		buffer[strcspn(buffer, "\n")] = '\0';
		char *str = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));

		if (str == NULL) {
			fprintf(stderr, "Error allocating memory for str");
			return NULL;
		}
		else { strcpy_s(str, strlen(buffer) + 1, buffer); }
		systemCall(CLEAR_BUFFER);
		free(buffer);
		return str;
	}
}

char *readString(void) {
	char *buffer = (char*)malloc(sizeof(char) * DEF_SIZE);
	gets_s(buffer, DEF_SIZE);
	buffer[strcspn(buffer, "\n")] = '\0';
	char *str = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));

	if (str == NULL) {
		fprintf(stderr, "Error allocating memory for str");
		return NULL;
	}
	else { strcpy_s(str, strlen(buffer) + 1, buffer); }
	systemCall("clearBuffer");
	free(buffer);
	return str;
}


char *readStringA(const char command[]) {
	if (strcmp(command, AUTO_SIZE) == 0) {
		const rsize_t maxSize = LONG_MAX;

		char *buffer = (char*)malloc(sizeof(char) * maxSize);
		gets_s(buffer, maxSize);
		buffer[strcspn(buffer, "\n")] = '\0';
		char *str = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));

		if (str == NULL) {
			fprintf(stderr, "Error allocating memory for str");
			return NULL;
		}
		else { strcpy_s(str, strlen(buffer) + 1, buffer); }
		systemCall(CLEAR_BUFFER);
		free(buffer);
		return str;
	} else {
		puts("command not valid, returning null string");
		return NULL;
	}

		
}


void systemCall(const char *buffer) {
	// #Commands
	const char clearBuffer[] = {"clearBuffer"};

	if (strcmp(buffer, clearBuffer) == 0) { fflush(stdin); }
}