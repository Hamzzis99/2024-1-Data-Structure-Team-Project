#include "linkedlist.h"
#include <stdlib.h>

void list_init(List* lp) {
    lp->head = NULL;
    lp->tail = NULL; // tail �ʱ�ȭ
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
        lp->tail = newNode; // ����Ʈ�� ��������� head�� tail ��� ���ο� ��带 ����Ŵ
    }
    else {
        lp->tail->next = newNode;
        lp->tail = newNode; // ���ο� ��带 tail�� ����
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
            lp->tail = NULL; // ����Ʈ�� ��ԵǸ� tail�� NULL�� ����
        }
    }
    else {
        lp->prev->next = lp->cur->next;
        if (rnode == lp->tail) {
            lp->tail = lp->prev; // tail�� ������ ���, ���� ��带 tail�� ����
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
