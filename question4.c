#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    int score;
    int accessed;
};

struct Shelf {
    struct Book books[100];
    int capacity;
    int size;
    int time;
};

void addBook(struct Shelf *shelf, int id, int score) {
    for (int i = 0; i < shelf->size; i++) {
        if (shelf->books[i].id == id) {
            shelf->books[i].score = score;
            shelf->books[i].accessed = shelf->time++;
            return;
        }
    }
    
    if (shelf->size < shelf->capacity) {
        shelf->books[shelf->size].id = id;
        shelf->books[shelf->size].score = score;
        shelf->books[shelf->size].accessed = shelf->time++;
        shelf->size++;
    } else {
        int minIndex = 0;
        for (int i = 1; i < shelf->size; i++) {
            if (shelf->books[i].accessed < shelf->books[minIndex].accessed) {
                minIndex = i;
            }
        }
        shelf->books[minIndex].id = id;
        shelf->books[minIndex].score = score;
        shelf->books[minIndex].accessed = shelf->time++;
    }
}

int accessBook(struct Shelf *shelf, int id) {
    for (int i = 0; i < shelf->size; i++) {
        if (shelf->books[i].id == id) {
            shelf->books[i].accessed = shelf->time++;
            return shelf->books[i].score;
        }
    }
    return -1;
}

int main() {
    struct Shelf shelf;
    int Q;
    
    scanf("%d %d", &shelf.capacity, &Q);
    shelf.size = 0;
    shelf.time = 0;
    
    for (int i = 0; i < Q; i++) {
        char operation[10];
        scanf("%s", operation);
        
        if (strcmp(operation, "ADD") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            addBook(&shelf, x, y);
        } else if (strcmp(operation, "ACCESS") == 0) {
            int x;
            scanf("%d", &x);
            int result = accessBook(&shelf, x);
            printf("%d\n", result);
        }
    }
    
    return 0;
}
