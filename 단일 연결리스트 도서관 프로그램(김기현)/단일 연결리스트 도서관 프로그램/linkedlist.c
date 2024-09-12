#include "linkedlist.h"
#include <stdlib.h>

void list_init(List* lp) {
    lp->head = NULL;
    lp->tail = NULL; // tail 초기화
    lp->cur = NULL;
    lp->prev = NULL;
    lp->data_cnt = 0;
}

void insert_last(List* lp, LLData data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (lp->head == NULL) {
        lp->head = newNode;
        lp->tail = newNode; // 리스트가 비어있으면 head와 tail 모두 새로운 노드를 가리킴
    }
    else {
        lp->tail->next = newNode;
        lp->tail = newNode; // 새로운 노드를 tail로 설정
    }
    lp->data_cnt++;
}

int search_first(List* lp, LLData* pdata) {
    if (lp->head == NULL) return 0;
    lp->cur = lp->head;
    lp->prev = NULL;
    *pdata = lp->cur->data;
    return 1;
}

int search_next(List* lp, LLData* pdata) {
    if (lp->cur->next == NULL) return 0;
    lp->prev = lp->cur;
    lp->cur = lp->cur->next;
    *pdata = lp->cur->data;
    return 1;
}

LLData remove_node(List* lp) {
    Node* rnode = lp->cur;
    LLData rdata = rnode->data;

    if (rnode == lp->head) {
        lp->head = lp->head->next;
        if (lp->head == NULL) {
            lp->tail = NULL; // 리스트가 비게되면 tail도 NULL로 설정
        }
    }
    else {
        lp->prev->next = lp->cur->next;
        if (rnode == lp->tail) {
            lp->tail = lp->prev; // tail이 삭제된 경우, 이전 노드를 tail로 설정
        }
    }

    lp->cur = lp->prev;
    free(rnode);
    lp->data_cnt--;
    return rdata;
}

int count(List* lp) {
    return lp->data_cnt;
}
