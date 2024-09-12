#pragma once
#ifndef __BOOKINFO_H__
#define __BOOKINFO_H__

#define BASIC_LEN 20
#define DATA_LEN 12

typedef struct _bookinfo {
    int id; // 도서 등록번호
    int category_id; // 도서 분류번호
    char name[BASIC_LEN]; // 도서 이름
    char purchase_date[DATA_LEN]; // 구매 날짜
    char author[BASIC_LEN]; // 저자 이름
} BookInfo;

BookInfo* bookinfo_make_data(int id, int category_id, char* name, char* date, char* author);
void bookinfo_show(BookInfo* pinfo);
int bookinfo_name_compare(BookInfo* pinfo, char* name);
int bookinfo_name_contains(BookInfo* pinfo, char* name);

#endif
