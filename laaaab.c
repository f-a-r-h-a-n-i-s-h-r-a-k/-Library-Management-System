#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    int bookId;
    char bookTitle[100];
    char bookAuthor[100];
    float bookPrice;
    int bookYear;
    struct Book *next;
} Book;

Book* addBook(Book *head);
Book* deleteBook(Book *head, int bookId);
void searchBook(Book *head, int searchOption, const char *searchValue);
Book* sortBooks(Book *head, int sortOption);
void displayBooks(Book *head);
Book* createBook(int bookId, const char *bookTitle, const char *bookAuthor, float bookPrice, int bookYear);
int compareBooks(Book *bookA, Book *bookB, int sortOption);
void swapBooks(Book *bookA, Book *bookB);

int main() {
    Book *head = NULL;
    int userChoice, bookId;
    char searchValue[100];

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book\n");
        printf("4. Sort Books\n");
        printf("5. Display Books\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                head = addBook(head);
                break;
            case 2:
                printf("Enter Book ID to delete: ");
                scanf("%d", &bookId);
                head = deleteBook(head, bookId);
                break;
            case 3:
                printf("Search by: 1. ID  2. Title  3. Author\n");
                printf("Enter option: ");
                int searchOption;
                scanf("%d", &searchOption);
                printf("Enter search value: ");
                getchar();
                fgets(searchValue, 100, stdin);
                searchValue[strcspn(searchValue, "\n")] = '\0';
                searchBook(head, searchOption, searchValue);
                break;
            case 4:
                printf("Sort by: 1. Title  2. Author  3. Price  4. Year\n");
                printf("Enter option: ");
                int sortOption;
                scanf("%d", &sortOption);
                head = sortBooks(head, sortOption);
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
    } while (userChoice != 6);

    return 0;
}

Book* createBook(int bookId, const char *bookTitle, const char *bookAuthor, float bookPrice, int bookYear) {
    Book *newBook = (Book *)malloc(sizeof(Book));
    newBook->bookId = bookId;
    strcpy(newBook->bookTitle, bookTitle);
    strcpy(newBook->bookAuthor, bookAuthor);
    newBook->bookPrice = bookPrice;
    newBook->bookYear = bookYear;
    newBook->next = NULL;
    return newBook;
}

Book* addBook(Book *head) {
    int bookId, bookYear;
    float bookPrice;
    char bookTitle[100], bookAuthor[100];

    printf("Enter Book ID: ");
    scanf("%d", &bookId);
    getchar();
    printf("Enter Title: ");
    fgets(bookTitle, 100, stdin);
    bookTitle[strcspn(bookTitle, "\n")] = '\0';
    printf("Enter Author: ");
    fgets(bookAuthor, 100, stdin);
    bookAuthor[strcspn(bookAuthor, "\n")] = '\0';
    printf("Enter Price: ");
    scanf("%f", &bookPrice);
    printf("Enter Year: ");
    scanf("%d", &bookYear);

    Book *newBook = createBook(bookId, bookTitle, bookAuthor, bookPrice, bookYear);

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

void displayBooks(Book *head) {
    if (!head) {
        printf("No books available.\n");
        return;
    }

    printf("\nBook Inventory:\n");
    printf("ID\tTitle\t\tAuthor\t\tPrice\tYear\n");

    Book *temp = head;
    while (temp) {
        printf("%d\t%s\t\t%s\t\t%.2f\t%d\n", temp->bookId, temp->bookTitle,
               temp->bookAuthor, temp->bookPrice, temp->bookYear);
        temp = temp->next;
    }
}
