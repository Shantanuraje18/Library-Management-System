#include<stdio.h>
#include<string.h>

#define MAX_BOOKS 100
#define TITLE_LEN 100
#define AUTHOR_LEN 50

typedef struct {
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int id;
    int available; // 1 if available, 0 if borrowed (not used in this simple version)
} Book;

Book library[MAX_BOOKS];
int bookCount = 0;

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }
    printf("Enter book title: ");
    getchar(); // to consume leftover newline
    fgets(library[bookCount].title, TITLE_LEN, stdin);
    library[bookCount].title[strcspn(library[bookCount].title, "\n")] = 0; // remove newline

    printf("Enter author name: ");
    fgets(library[bookCount].author, AUTHOR_LEN, stdin);
    library[bookCount].author[strcspn(library[bookCount].author, "\n")] = 0;

    library[bookCount].id = bookCount + 1;
    library[bookCount].available = 1;
    bookCount++;
    printf("Book added successfully.\n");
}

void displayBooks() {
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }
    printf("\n%-5s %-30s %-20s\n", "ID", "Title", "Author");
    printf("-------------------------------------------------------\n");
    int i;
    for (i = 0; i < bookCount; i++) {
        printf("%-5d %-30s %-20s\n", library[i].id, library[i].title, library[i].author);
    }
    printf("\n");
}

void searchBook() {
    char searchTitle[TITLE_LEN];
    printf("Enter title to search: ");
    getchar(); // consume newline
    fgets(searchTitle, TITLE_LEN, stdin);
    searchTitle[strcspn(searchTitle, "\n")] = 0;

    int found = 0;
    int i;
    for ( i = 0; i < bookCount; i++) {
        if (strcasecmp(library[i].title, searchTitle) == 0) {
            printf("Book found:\nID: %d\nTitle: %s\nAuthor: %s\n", library[i].id, library[i].title, library[i].author);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book with title '%s' not found.\n", searchTitle);
    }
}

void deleteBook() {
    char delTitle[TITLE_LEN];
    printf("Enter title to delete: ");
    getchar(); // consume newline
    fgets(delTitle, TITLE_LEN, stdin);
    delTitle[strcspn(delTitle, "\n")] = 0;

    int foundIndex = -1;
    int i;
    
    for ( i = 0; i < bookCount; i++) {
        if (strcasecmp(library[i].title, delTitle) == 0) {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1) {
        printf("Book with title '%s' not found.\n", delTitle);
        return;
    }
    for ( i = foundIndex; i < bookCount - 1; i++) {
        library[i] = library[i + 1];
        library[i].id = i + 1;
    }
    bookCount--;
    printf("Book deleted successfully.\n");
}

void menu() {
    printf("Library Management System\n");
    printf("-------------------------\n");
    printf("1. Add Book\n");
    printf("2. Display Books\n");
    printf("3. Search Book by Title\n");
    printf("4. Delete Book by Title\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    do {
        menu();
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // clear invalid input
            printf("Invalid input. Please enter a number.\n");
            choice = 0;
            continue;
        }
        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice! Please select between 1-5.\n");
        }
    } while (choice != 5);

    return 0;
}

