#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linkedlist.h"
#include "bookinfo.h"

#define TOTAL_CATEGORIES 10 // ���� ��Ϲ�ȣ�� ����
#define BOOKS_PER_CATEGORY 10000 // �з��� ������ ����

int book_id_counter = 1; // ���� ��Ϲ�ȣ �ʱ�ȭ
int book_name_counter = 1; // ���� �̸� ī���� �ʱ�ȭ

// ��ü ���� ����Ʈ
List all_books;

// ����ڷκ��� �з���ȣ�� �Է¹޴� �Լ�
int get_category_id() {
    int category_id;
    while (1) {
        printf("�з� ��ȣ�� �Է��ϼ��� (000, 100, 200, 300, 400, 500, 600, 700, 800, 900): ");
        scanf("%d", &category_id);
        getchar();
        if (category_id == 0 || category_id == 100 || category_id == 200 || category_id == 300 ||
            category_id == 400 || category_id == 500 || category_id == 600 || category_id == 700 ||
            category_id == 800 || category_id == 900) {
            break; // �ùٸ� �з���ȣ �Է� �� ���� ����
        }
        else {
            printf("�ùٸ� ��ȣ�� �Է��ϼ���.\n");
        }
    }
    return category_id; // �з���ȣ ��ȯ
}

// �������� ���� �̸� ���� �Լ�
void generate_sequential_book_name(char* name) {
    snprintf(name, BASIC_LEN, "å%d", book_name_counter++);
}

// ������ ���ڿ� ���� �Լ�
void generate_random_string(char* str, int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < length - 1; i++) {
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    str[length - 1] = '\0';
}

// ������ ��¥ ���� �Լ�
void generate_random_date(char* date) {
    int year = rand() % 21 + 2000; // 2000 ~ 2020
    int month = rand() % 12 + 1; // 1 ~ 12
    int day = rand() % 28 + 1; // 1 ~ 28
    snprintf(date, DATA_LEN, "%04d-%02d-%02d", year, month, day);
}

// ���� ������ ����Ʈ�� �߰��ϴ� �Լ�
void insert_book(int category_id, char* name, char* date, char* author) {
    BookInfo* newBook = bookinfo_make_data(book_id_counter++, category_id, name, date, author); // ���� ���� ����
    if (newBook) {
        insert_last(&all_books, newBook); // ��ü ���� ����Ʈ ���� ����
    }
}

// ��� ī�װ��� ������ ������ �߰��ϴ� �Լ�
void populate_books() {
    printf("%d���� ������ ������Դϴ�...\n", BOOKS_PER_CATEGORY * TOTAL_CATEGORIES);
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
    printf("���� ����� �Ϸ�Ǿ����ϴ�.\n");
}

// ���� �̸��� �˻��ϴ� ���� Ž�� �Լ�
void linear_search_book() {
    char name[BASIC_LEN];
    BookInfo* pdata;
    int found = 0;
    int count = 0;

    printf("�˻��� å �̸�: ");
    fgets(name, BASIC_LEN, stdin);
    name[strcspn(name, "\n")] = 0; // �Է¹��� ���ڿ����� ���� ���� ����

    clock_t start_time = clock(); // �˻� ���� �ð�
    if (search_first(&all_books, (LLData*)&pdata)) { // ù ��° ��� �˻�
        if (bookinfo_name_contains(pdata, name)) { // ������ �κ������� ��ġ�ϴ��� Ȯ��
            bookinfo_show(pdata);
            found = 1;
            count++;
        }
        while (search_next(&all_books, (LLData*)&pdata)) { // ���� ��� �˻�
            if (bookinfo_name_contains(pdata, name)) {
                bookinfo_show(pdata);
                found = 1;
                count++;
            }
        }
    }
    clock_t end_time = clock(); // �˻� ���� �ð�

    if (!found) {
        printf("å�� ã�� �� �����ϴ�.\n");
    }
    else {
        double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("�˻� �ð�: %.2f��\n", time_taken);
        printf("�˻��� ���� ����: %d��\n", count);
    }
}

// ���� ������ �����ϴ� �Լ�
void delete_book() {
    char name[BASIC_LEN];
    BookInfo* pdata;

    printf("������ å �̸�: ");
    fgets(name, BASIC_LEN, stdin);
    name[strcspn(name, "\n")] = 0; // �Է¹��� ���ڿ����� ���� ���� ����

    clock_t start_time = clock(); // ���� ���� �ð�

    if (search_first(&all_books, (LLData*)&pdata)) {
        if (bookinfo_name_compare(pdata, name) == 0) {
            pdata = remove_node(&all_books);
            free(pdata); // �޸� ����
            clock_t end_time = clock(); // ���� ���� �ð�
            double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            printf("å ������ �����Ǿ����ϴ�. (�ҿ� �ð�: %.2f��)\n", time_taken);
            return;
        }
        while (search_next(&all_books, (LLData*)&pdata)) {
            if (bookinfo_name_compare(pdata, name) == 0) {
                pdata = remove_node(&all_books);
                free(pdata); // �޸� ����
                clock_t end_time = clock(); // ���� ���� �ð�
                double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
                printf("å ������ �����Ǿ����ϴ�. (�ҿ� �ð�: %.2f��)\n", time_taken);
                return;
            }
        }
    }

    clock_t end_time = clock(); // ���� ���� �ð�
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("å�� ã�� �� �����ϴ�. (�ҿ� �ð�: %.2f��)\n", time_taken);
}

// ��ü ���� ������ ���� ��Ϲ�ȣ ������� ����ϴ� �Լ�
void show_all() {
    BookInfo* pdata;
    int count = 0;
    clock_t start_time = clock(); // ��� ���� �ð�
    printf("\n��ü å ���:\n");
    if (search_first(&all_books, (LLData*)&pdata)) {
        do {
            bookinfo_show(pdata);
            count++;
        } while (search_next(&all_books, (LLData*)&pdata));
    }
    clock_t end_time = clock(); // ��� ���� �ð�
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("��ü ��� ���� �ð�: %.2f��\n", time_taken);
    printf("��ü ���� ����: %d��\n", count);
}

// ���α׷� ���� �� ��� ���� ������ �����ϴ� �Լ�
void book_exit() {
    BookInfo* pdata;
    while (search_first(&all_books, (LLData*)&pdata)) {
        pdata = remove_node(&all_books);
        free(pdata); // �޸� ����
    }
}

// �޴��� ����ϴ� �Լ�
void show_menu(void) {
    printf("\n==========================\n");
    printf("1. å ���� �߰� \n");
    printf("2. å ���� �˻� \n");
    printf("3. å ���� ����\n");
    printf("4. ��ü ��� ����\n");
    printf("5. ����\n");
    printf("==========================\n");
}

// ���ο� ���� ������ ����ڷκ��� �Է¹޾� �߰��ϴ� �Լ�
void add_new_book() {
    int category_id = get_category_id();
    char name[BASIC_LEN];
    char date[DATA_LEN];
    char author[BASIC_LEN];

    printf("å �̸�: ");
    fgets(name, BASIC_LEN, stdin);
    name[strcspn(name, "\n")] = 0; // ���� ���� ����

    printf("���� ��¥ (YYYY-MM-DD): ");
    fgets(date, DATA_LEN, stdin);
    date[strcspn(date, "\n")] = 0; // ���� ���� ����

    printf("����: ");
    fgets(author, BASIC_LEN, stdin);
    author[strcspn(author, "\n")] = 0; // ���� ���� ����

    insert_book(category_id, name, date, author);
}

// ���� �Լ�
int main() {
    list_init(&all_books);
    srand(time(NULL)); // ���� �õ� ����

    clock_t start_time = clock(); // ���� ��� ���� �ð�
    populate_books(); // �� ī�װ��� ������ ���� �߰�
    clock_t end_time = clock(); // ���� ��� ���� �ð�

    double registration_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("�� %d���� ������ ��ϵǾ����ϴ�.\n", book_name_counter - 1);
    printf("���� ��� �ð�: %.2f��\n", registration_time);

    int cmd = 0;
    while (1) {
        show_menu();
        printf("����: ");
        scanf("%d", &cmd);
        getchar(); // ���� ���� ����

        switch (cmd) {
        case 1:
            add_new_book(); // ���ο� ���� ���� �߰�
            break;
        case 2:
            linear_search_book(); // å ���� �˻�
            break;
        case 3:
            delete_book(); // å ���� ����
            break;
        case 4:
            show_all(); // ��ü ��� ����
            break;
        case 5:
            book_exit(); // ���α׷� ����
            break;
        }
        if (cmd == 5)
            break;
    }
    printf("���α׷��� ����˴ϴ�.\n");
    return 0;
}
