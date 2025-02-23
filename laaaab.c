#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    int id;
    char title[100];
    char author[100];
    float price;
    int year;
    struct Book *next;
} Book;

Book* addBook(Book *head);
Book* deleteBook(Book *head, int id);
void searchBook(Book *head, int option, const char *value);
Book* sortBooks(Book *head, int option);
void displayBooks(Book *head);
Book* createBook(int id, const char *title, const char *author, float price, int year);
int compare(Book *a, Book *b, int option);
void swap(Book *a, Book *b);

int main() {
    Book *head = NULL;
    int choice, id;
    char value[100];

    do {
        printf("\n A Library Management System\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book\n");
        printf("4. Sort Books\n");
        printf("5. Display Books\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                head = addBook(head);
                break;
            case 2:
                printf("Enter Book ID to delete: ");
                scanf("%d", &id);
                head = deleteBook(head, id);
                break;
            case 3:
                printf("Search by: 1. ID  2. Title  3. Author\n");
                printf("Enter option: ");
                int option;
                scanf("%d", &option);
                printf("Enter search value: ");
                getchar();
                fgets(value, 100, stdin);
                value[strcspn(value, "\n")] = '\0'; // Remove trailing newline
                searchBook(head, option, value);
                break;
            case 4:
                printf("Sort by: 1. Title  2. Author  3. Price  4. Year\n");
                printf("Enter option: ");
                scanf("%d", &option);
                head = sortBooks(head, option);
                break;
            case 5:
                displayBooks(head);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

Book* createBook(int id, const char *title, const char *author, float price, int year) {
    Book *newBook = (Book *)malloc(sizeof(Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->price = price;
    newBook->year = year;
    newBook->next = NULL;
    return newBook;
}


Book* addBook(Book *head) {
    int id, year;
    float price;
    char title[100], author[100];

    printf("Enter Book ID: ");
    scanf("%d", &id);
    getchar();
    printf("Enter Title: ");
    fgets(title, 100, stdin);
    title[strcspn(title, "\n")] = '\0';
    printf("Enter Author: ");
    fgets(author, 100, stdin);
    author[strcspn(author, "\n")] = '\0';
    printf("Enter Price: ");
    scanf("%f", &price);
    printf("Enter Year: ");
    scanf("%d", &year);

    Book *newBook = createBook(id, title, author, price, year);

    if (!head) {
        return newBook;
    }

    Book *temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newBook;

    return head;
}

Book* deleteBook(Book *head, int id) {
    if (!head) {
        printf("No books available.\n");
        return head;
    }

    if (head->id == id) {
        Book *temp = head;
        head = head->next;
        free(temp);
        printf("Book has been deleted.\n");
        return head;
    }

    Book *current = head;
    while (current->next && current->next->id != id) {
        current = current->next;
    }

    if (current->next) {
        Book *temp = current->next;
        current->next = current->next->next;
        free(temp);
        printf("Book has been deleted .\n");
    } else {
        printf("Book with ID %d not found.\n", id);
    }

    return head;
}

void searchBook(Book *head, int option, const char *value) {
    Book *temp = head;
    int found = 0;

    while (temp) {
        if ((option == 1 && temp->id == atoi(value)) ||
            (option == 2 && strcasecmp(temp->title, value) == 0) ||
            (option == 3 && strcasecmp(temp->author, value) == 0)) {
            printf("\nBook Found:\n");
            printf("ID: %d | Title: %s | Author: %s | Price: %.2f | Year: %d\n",
                   temp->id, temp->title, temp->author, temp->price, temp->year);
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No book found.\n");
    }
}


Book* sortBooks(Book *head, int option) {
    if (!head || !head->next) {
        printf("Not enough books to sort.\n");
        return head;
    }

    for (Book *i = head; i->next; i = i->next) {
        Book *min = i;
        for (Book *j = i->next; j; j = j->next) {
            if (compare(min, j, option) > 0) {
                min = j;
            }
        }
        if (min != i) {
            swap(min, i);
        }
    }

    printf("\nSorted Inventory:\n");
    displayBooks(head);

    return head;
}

int compare(Book *a, Book *b, int option) {
    switch (option) {
        case 1: return strcasecmp(a->title, b->title);
        case 2: return strcasecmp(a->author, b->author);
        case 3: return (a->price > b->price) - (a->price < b->price);
        case 4: return (b->year > a->year) - (b->year < a->year);
        default: return 0;
    }
}

void swap(Book *a, Book *b) {
    Book temp = *a;
    *a = *b;
    *b = temp;

    Book *tempNext = a->next;
    a->next = b->next;
    b->next = tempNext;
}


void displayBooks(Book *head) {
    if (!head) {
        printf("No books available.\n");
        return;
    }

    printf("\nBook Inventory:\n");
    printf("ID  \tTitle\t\tAuthor\t\tPrice     \tYear\n");

    Book *temp = head;
    while (temp) {
        printf("%d\t%s\t\t%s\t\t%.2f     \t%d\n", temp->id, temp->title,
            temp->author, temp->price, temp->year);
            temp = temp->next;
    }
}
