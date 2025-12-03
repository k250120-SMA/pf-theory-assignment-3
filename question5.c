#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TextEditor {
    char **lines;
    int count;
    int capacity;
};

void initializeEditor(struct TextEditor *editor, int initialCapacity);
void expandCapacity(struct TextEditor *editor);
void insertLine(struct TextEditor *editor, int index, const char *text);
void deleteLine(struct TextEditor *editor, int index);
void printAllLines(struct TextEditor *editor);
void freeAll(struct TextEditor *editor);
void shrinkToFit(struct TextEditor *editor);
void saveToFile(struct TextEditor *editor, const char *filename);
void loadFromFile(struct TextEditor *editor, const char *filename);

void initializeEditor(struct TextEditor *editor, int initialCapacity) {
    editor->lines = (char**)malloc(initialCapacity * sizeof(char*));
    if (editor->lines == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    editor->count = 0;
    editor->capacity = initialCapacity;
}

void expandCapacity(struct TextEditor *editor) {
    int newCapacity = editor->capacity * 2;
    char **newLines = (char**)realloc(editor->lines, newCapacity * sizeof(char*));
    if (newLines == NULL) {
        printf("Memory expansion failed!\n");
        exit(1);
    }
    editor->lines = newLines;
    editor->capacity = newCapacity;
}

void insertLine(struct TextEditor *editor, int index, const char *text) {
    if (index < 0 || index > editor->count) {
        printf("Invalid index! Must be between 0 and %d\n", editor->count);
        return;
    }
    
    if (editor->count == editor->capacity) {
        expandCapacity(editor);
    }
    
    if (index < editor->count) {
        memmove(&editor->lines[index + 1], &editor->lines[index], 
                (editor->count - index) * sizeof(char*));
    }
    
    editor->lines[index] = (char*)malloc(strlen(text) + 1);
    if (editor->lines[index] == NULL) {
        printf("Memory allocation for line failed!\n");
        return;
    }
    strcpy(editor->lines[index], text);
    editor->count++;
    
    printf("Line inserted at position %d\n", index);
}

void deleteLine(struct TextEditor *editor, int index) {
    if (index < 0 || index >= editor->count) {
        printf("Invalid index! Must be between 0 and %d\n", editor->count - 1);
        return;
    }
    
    free(editor->lines[index]);
    
    if (index < editor->count - 1) {
        memmove(&editor->lines[index], &editor->lines[index + 1], 
                (editor->count - index - 1) * sizeof(char*));
    }
    
    editor->count--;
    printf("Line deleted from position %d\n", index);
}

void printAllLines(struct TextEditor *editor) {
    printf("\n=== TEXT EDITOR CONTENT ===\n");
    if (editor->count == 0) {
        printf("No lines in editor.\n");
        return;
    }
    
    for (int i = 0; i < editor->count; i++) {
        printf("%d: %s\n", i + 1, editor->lines[i]);
    }
    printf("Total lines: %d\n", editor->count);
}

void freeAll(struct TextEditor *editor) {
    for (int i = 0; i < editor->count; i++) {
        free(editor->lines[i]);
    }
    free(editor->lines);
    editor->count = 0;
    editor->capacity = 0;
    printf("All memory freed.\n");
}

void shrinkToFit(struct TextEditor *editor) {
    if (editor->count < editor->capacity) {
        char **newLines = (char**)realloc(editor->lines, editor->count * sizeof(char*));
        if (newLines == NULL) {
            printf("Shrink operation failed!\n");
            return;
        }
        editor->lines = newLines;
        editor->capacity = editor->count;
        printf("Memory shrunk to fit %d lines\n", editor->count);
    }
}

void saveToFile(struct TextEditor *editor, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing!\n");
        return;
    }
    
    for (int i = 0; i <editor->count; i++) {
        fprintf(file, "%s\n", editor->lines[i]);
    }
    
    fclose(file);
    printf("Saved %d lines to '%s'\n", editor->count, filename);
}

void loadFromFile(struct TextEditor *editor, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file for reading!\n");
        return;
    }
    
    freeAll(editor);
    initializeEditor(editor, 10);
    
    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        insertLine(editor, editor->count, buffer);
    }
    
    fclose(file);
    printf("Loaded %d lines from '%s'\n", editor->count, filename);
}

int main() {
    struct TextEditor editor;
    initializeEditor(&editor, 5);
    
    int choice;
    char filename[100];
    char text[1000];
    int index;
    
    while (1) {
        printf("\n=== TEXT EDITOR MENU ===\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Print All Lines\n");
        printf("4. Shrink to Fit\n");
        printf("5. Save to File\n");
        printf("6. Load from File\n");
        printf("7. Clear All\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                if (editor.count == 0) {
                    printf("Editor is empty. Enter text for first line: ");
                } else {
                    printf("Enter line index (0-%d): ", editor.count);
                    scanf("%d", &index);
                    getchar();
                }
                printf("Enter text: ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0';
                insertLine(&editor, editor.count, text);
                break;
                
            case 2:
                if (editor.count == 0) {
                    printf("No lines to delete!\n");
                    break;
                }
                printf("Enter line index to delete (0-%d): ", editor.count - 1);
                scanf("%d", &index);
                getchar();
                deleteLine(&editor, index);
                break;
                
            case 3:
                printAllLines(&editor);
                printf("Capacity: %d, Count: %d\n", editor.capacity, editor.count);
                break;
                
            case 4:
                shrinkToFit(&editor);
                break;
                
            case 5:
                printf("Enter filename to save: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                saveToFile(&editor, filename);
                break;
                
            case 6:
                printf("Enter filename to load: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                loadFromFile(&editor, filename);
                break;
                
            case 7:
                freeAll(&editor);
                initializeEditor(&editor, 5);
                break;
                
            case 8:
                freeAll(&editor);
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
