#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MENU_SIZE 5
#define MENU_INITIAL_VALUE -1
#define MENU_EXIT 0
#define MENU_SHOW 1
#define MENU_SHOWALL 2
#define MENU_ADD 3
#define MENU_REMOVE 4

static char *menu_command[MENU_SIZE] = {"EXIT", "SHOW", "SHOWALL", "ADD", "REMOVE"};

void run();
int get_command();
char *get_string();

int main() {
    run();
    return EXIT_SUCCESS;
}

void run() {
    int command = MENU_INITIAL_VALUE;
    while (command) {
        command = get_command();
        switch (command) {
            case MENU_EXIT:
                printf("MENU_EXIT\n");
                break;
            case MENU_SHOW:
                printf("MENU_SHOW\n");
                break;
            case MENU_SHOWALL:
                printf("MENU_SHOWALL\n");
                break;
            case MENU_ADD:
                printf("MENU_ADD\n");
                break;
            case MENU_REMOVE:
                printf("MENU_REMOVE\n");
                break;
            default:
                break;
        }
    }
}

int get_command() {
    int result = MENU_INITIAL_VALUE;
    char *line = get_string();
    for (int i = 0; i < MENU_SIZE; i++) {
        if (!strcmp(line, menu_command[i])) {
            result = i;
            break;
        }
    }
    free(line);

    return result;
}

/* Функция получения динамической строки */
char *get_string() {
    int len = 0;
    int size = 1;
    char *line = (char *)malloc(sizeof(char));

    char c = getchar();
    while (c != '\n' && c != -1) {
        line[(len)++] = c;
        if (len >= size) {
            size *= 2;
            char *tmp = (char *)realloc(line, size * sizeof(char));
            if (tmp != NULL) {
                line = tmp;
            } else {
                printf("Not memory");
            }
        }
        c = getchar();
    }
    line[len] = '\0';

    return line;
}