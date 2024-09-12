#include "bookinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BookInfo* bookinfo_make_data(int id, int category_id, char* name, char* date, char* author) {
    BookInfo* newBook = (BookInfo*)malloc(sizeof(BookInfo));
    newBook->id = id;
    newBook->category_id = category_id;
    strncpy(newBook->name, name, BASIC_LEN);
    strncpy(newBook->purchase_date, date, DATA_LEN);
    strncpy(newBook->author, author, BASIC_LEN);
    return newBook;
}

void bookinfo_show(BookInfo* pinfo) {
    printf("등록번호: %d, 분류번호: %d, 이름: %s, 구매날짜: %s, 저자: %s\n",
        pinfo->id, pinfo->category_id, pinfo->name, pinfo->purchase_date, pinfo->author);
}

int bookinfo_name_compare(BookInfo* pinfo, char* name) {
    return strncmp(pinfo->name, name, BASIC_LEN);
}

int bookinfo_name_contains(BookInfo* pinfo, char* name) {
    return strstr(pinfo->name, name) != NULL;
}
