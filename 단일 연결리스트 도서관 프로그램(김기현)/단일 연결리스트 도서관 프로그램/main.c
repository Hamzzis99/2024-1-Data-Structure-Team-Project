#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linkedlist.h"
#include "bookinfo.h"

#define TOTAL_CATEGORIES 10 // 도서 등록번호의 개수
#define BOOKS_PER_CATEGORY 10000 // 분류당 도서의 개수

int book_id_counter = 1; // 도서 등록번호 초기화
int book_name_counter = 1; // 도서 이름 카운터 초기화

// 전체 도서 리스트
List all_books;

// 사용자로부터 분류번호를 입력받는 함수
int get_category_id() {
    int category_id;
    while (1) {
        printf("분류 번호를 입력하세요 (000, 100, 200, 300, 400, 500, 600, 700, 800, 900): ");
        scanf("%d", &category_id);
        getchar();
        if (category_id == 0 || category_id == 100 || category_id == 200 || category_id == 300 ||
            category_id == 400 || category_id == 500 || category_id == 600 || category_id == 700 ||
            category_id == 800 || category_id == 900) {
            break; // 올바른 분류번호 입력 시 루프 종료
        }
        else {
            printf("올바른 번호를 입력하세요.\n");
        }
    }
    return category_id; // 분류번호 반환
}

// 연속적인 도서 이름 생성 함수
void generate_sequential_book_name(char* name) {
    snprintf(name, BASIC_LEN, "책%d", book_name_counter++);
}

// 랜덤한 문자열 생성 함수
void generate_random_string(char* str, int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < length - 1; i++) {
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    str[length - 1] = '\0';
}

// 랜덤한 날짜 생성 함수
void generate_random_date(char* date) {
    int year = rand() % 21 + 2000; // 2000 ~ 2020
    int month = rand() % 12 + 1; // 1 ~ 12
    int day = rand() % 28 + 1; // 1 ~ 28
    snprintf(date, DATA_LEN, "%04d-%02d-%02d", year, month, day);
}

// 도서 정보를 리스트에 추가하는 함수
void insert_book(int category_id, char* name, char* date, char* author) {
    BookInfo* newBook = bookinfo_make_data(book_id_counter++, category_id, name, date, author); // 도서 정보 생성
    if (newBook) {
        insert_last(&all_books, newBook); // 전체 도서 리스트 끝에 삽입
    }
}

// 모든 카테고리에 랜덤한 도서를 추가하는 함수
void populate_books() {
    printf("%d개의 도서를 등록중입니다...\n", BOOKS_PER_CATEGORY * TOTAL_CATEGORIES);
    for (int i = 0; i < TOTAL_CATEGORIES; i++) {
        for (int j = 0; j < BOOKS_PER_CATEGORY; j++) {
            int category_id = i * 100;
            char name[BASIC_LEN];
            char date[DATA_LEN];
            char author[BASIC_LEN];

            generate_sequential_book_name(name);
            generate_random_date(date);
            generate_random_string(author, BASIC_LEN);

            insert_book(category_id, name, date, author);
        }
    }
    printf("도서 등록이 완료되었습니다.\n");
}

// 도서 이름을 검색하는 선형 탐색 함수
void linear_search_book() {
    char name[BASIC_LEN];
    BookInfo* pdata;
    int found = 0;
    int count = 0;

    printf("검색할 책 이름: ");
    fgets(name, BASIC_LEN, stdin);
    name[strcspn(name, "\n")] = 0; // 입력받은 문자열에서 개행 문자 제거

    clock_t start_time = clock(); // 검색 시작 시간
    if (search_first(&all_books, (LLData*)&pdata)) { // 첫 번째 노드 검색
        if (bookinfo_name_contains(pdata, name)) { // 제목이 부분적으로 일치하는지 확인
            bookinfo_show(pdata);
            found = 1;
            count++;
        }
        while (search_next(&all_books, (LLData*)&pdata)) { // 다음 노드 검색
            if (bookinfo_name_contains(pdata, name)) {
                bookinfo_show(pdata);
                found = 1;
                count++;
            }
        }
    }
    clock_t end_time = clock(); // 검색 종료 시간

    if (!found) {
        printf("책을 찾을 수 없습니다.\n");
    }
    else {
        double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("검색 시간: %.2f초\n", time_taken);
        printf("검색된 도서 개수: %d개\n", count);
    }
}

// 도서 정보를 삭제하는 함수
void delete_book() {
    char name[BASIC_LEN];
    BookInfo* pdata;

    printf("삭제할 책 이름: ");
    fgets(name, BASIC_LEN, stdin);
    name[strcspn(name, "\n")] = 0; // 입력받은 문자열에서 개행 문자 제거

    clock_t start_time = clock(); // 삭제 시작 시간

    if (search_first(&all_books, (LLData*)&pdata)) {
        if (bookinfo_name_compare(pdata, name) == 0) {
            pdata = remove_node(&all_books);
            free(pdata); // 메모리 해제
            clock_t end_time = clock(); // 삭제 종료 시간
            double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            printf("책 정보가 삭제되었습니다. (소요 시간: %.2f초)\n", time_taken);
            return;
        }
        while (search_next(&all_books, (LLData*)&pdata)) {
            if (bookinfo_name_compare(pdata, name) == 0) {
                pdata = remove_node(&all_books);
                free(pdata); // 메모리 해제
                clock_t end_time = clock(); // 삭제 종료 시간
                double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
                printf("책 정보가 삭제되었습니다. (소요 시간: %.2f초)\n", time_taken);
                return;
            }
        }
    }

    clock_t end_time = clock(); // 삭제 종료 시간
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("책을 찾을 수 없습니다. (소요 시간: %.2f초)\n", time_taken);
}

// 전체 도서 정보를 도서 등록번호 순서대로 출력하는 함수
void show_all() {
    BookInfo* pdata;
    int count = 0;
    clock_t start_time = clock(); // 출력 시작 시간
    printf("\n전체 책 목록:\n");
    if (search_first(&all_books, (LLData*)&pdata)) {
        do {
            bookinfo_show(pdata);
            count++;
        } while (search_next(&all_books, (LLData*)&pdata));
    }
    clock_t end_time = clock(); // 출력 종료 시간
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("전체 목록 보기 시간: %.2f초\n", time_taken);
    printf("전체 도서 개수: %d개\n", count);
}

// 프로그램 종료 시 모든 도서 정보를 삭제하는 함수
void book_exit() {
    BookInfo* pdata;
    while (search_first(&all_books, (LLData*)&pdata)) {
        pdata = remove_node(&all_books);
        free(pdata); // 메모리 해제
    }
}

// 메뉴를 출력하는 함수
void show_menu(void) {
    printf("\n==========================\n");
    printf("1. 책 정보 추가 \n");
    printf("2. 책 제목 검색 \n");
    printf("3. 책 정보 삭제\n");
    printf("4. 전체 목록 보기\n");
    printf("5. 종료\n");
    printf("==========================\n");
}

// 새로운 도서 정보를 사용자로부터 입력받아 추가하는 함수
void add_new_book() {
    int category_id = get_category_id();
    char name[BASIC_LEN];
    char date[DATA_LEN];
    char author[BASIC_LEN];

    printf("책 이름: ");
    fgets(name, BASIC_LEN, stdin);
    name[strcspn(name, "\n")] = 0; // 개행 문자 제거

    printf("구매 날짜 (YYYY-MM-DD): ");
    fgets(date, DATA_LEN, stdin);
    date[strcspn(date, "\n")] = 0; // 개행 문자 제거

    printf("저자: ");
    fgets(author, BASIC_LEN, stdin);
    author[strcspn(author, "\n")] = 0; // 개행 문자 제거

    insert_book(category_id, name, date, author);
}

// 메인 함수
int main() {
    list_init(&all_books);
    srand(time(NULL)); // 랜덤 시드 설정

    clock_t start_time = clock(); // 도서 등록 시작 시간
    populate_books(); // 각 카테고리에 랜덤한 도서 추가
    clock_t end_time = clock(); // 도서 등록 종료 시간

    double registration_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("총 %d개의 도서가 등록되었습니다.\n", book_name_counter - 1);
    printf("도서 등록 시간: %.2f초\n", registration_time);

    int cmd = 0;
    while (1) {
        show_menu();
        printf("선택: ");
        scanf("%d", &cmd);
        getchar(); // 개행 문자 제거

        switch (cmd) {
        case 1:
            add_new_book(); // 새로운 도서 정보 추가
            break;
        case 2:
            linear_search_book(); // 책 제목 검색
            break;
        case 3:
            delete_book(); // 책 정보 삭제
            break;
        case 4:
            show_all(); // 전체 목록 보기
            break;
        case 5:
            book_exit(); // 프로그램 종료
            break;
        }
        if (cmd == 5)
            break;
    }
    printf("프로그램이 종료됩니다.\n");
    return 0;
}
