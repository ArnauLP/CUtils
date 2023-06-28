#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

/*MACROS & CONSTANTS*/
#define DEF_SIZE 512
#define AUTO_SIZE "autoSize"
#define CLEAR_BUFFER "clearBuffer"

/*DATA STRUCTURES*/
typedef struct tNode {
	int data;
	struct tNode* next;
} tNode;

typedef struct tStack {
	tNode* first;
} tStack;

typedef struct tQueue {
	tNode* head;
	tNode* last;
} tQueue;

typedef struct tList {
	tNode* first;
} tList;

/****STACK****/
void stackInit(tStack* s);

void stackPush(tStack* s, const int elem);

void stackPop(tStack* s);

int stackTop(const tStack s);

bool stackEmpty(const tStack s);

void stackPopN(tStack* s, const int n);

void stackClear(tStack* s);

/****QUEUE****/
void queueInit(tQueue* q);

void enqueue(tQueue* q, const int elem);

void dequeue(tQueue* q);

int queueHead(const tQueue q);

bool queueEmpty(const tQueue q);

void queueSwapFirst2(tQueue* q);

/****LIST****/
void listInit(tList* l);

void listInsert(tList* l, const int elem, int index);

void listDelete(tList* l, int index);

int listGet(tList l, const int index);

bool listEnd(const tNode* n);

bool emptyList(const tList l);

tNode* getNode(const tList* l, const int index);

/*STRING MANIPULATION*/
//default readString func, define a size and it will read until \0 or \n or max characters specified
//useful for known size strings as it's more efficient
char* readStringD(const size_t maxSize);

//it will read a string with a maximum of 512 characters
//useful when it's only a name or small text
char* readString(void);

//reads string with a maximum of LONG_MAX characters (a lot)
//! Use command AUTO_SIZE or "autoSize", soon will be more command specifiers
char *readStringA(const char command[]);

//a command function, all avaiilable commands in MACROS FILE.
void systemCall(const char* buffer);