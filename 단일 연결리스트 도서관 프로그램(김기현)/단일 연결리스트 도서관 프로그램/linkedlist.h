#pragma once
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "bookinfo.h"

typedef BookInfo* LLData;

typedef struct _node {
    LLData data;
    struct _node* next;
} Node;

typedef struct _linkedlist {
    Node* head;
    Node* tail; // 리스트의 끝을 가리키는 포인터 추가
    Node* cur;
    Node* prev;
    int data_cnt;
} SLinkedList;

typedef SLinkedList List;

void list_init(List* lp);
void insert_last(List* lp, LLData data);
int search_first(List* lp, LLData* pdata);
int search_next(List* lp, LLData* pdata);
LLData remove_node(List* lp);
int count(List* lp);

#endif
