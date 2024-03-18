#include <stdio.h>
#include <stdlib.h>

void run();
char *get_string();
char get_separator();

int main() {
    run();
    return EXIT_SUCCESS;
}

void run() {
    char *line = get_string();
    char separator = get_separator();
    char *current_symbol = line;
    while (*current_symbol != '\0') {
        if (*current_symbol == ' ')
            printf("%c", separator);
        else
            printf("%c", *current_symbol);
        current_symbol++;
    }

    free(line);
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

/* Функция получения разделителя */
char get_separator() {
    char c = getchar();

    return c;
}