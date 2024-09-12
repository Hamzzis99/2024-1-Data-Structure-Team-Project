#pragma once
#ifndef __BOOKINFO_H__
#define __BOOKINFO_H__

#define BASIC_LEN 20
#define DATA_LEN 12

typedef struct _bookinfo {
    int id; // ���� ��Ϲ�ȣ
    int category_id; // ���� �з���ȣ
    char name[BASIC_LEN]; // ���� �̸�
    char purchase_date[DATA_LEN]; // ���� ��¥
    char author[BASIC_LEN]; // ���� �̸�
} BookInfo;

BookInfo* bookinfo_make_data(int id, int category_id, char* name, char* date, char* author);
void bookinfo_show(BookInfo* pinfo);
int bookinfo_name_compare(BookInfo* pinfo, char* name);
int bookinfo_name_contains(BookInfo* pinfo, char* name);

#endif
