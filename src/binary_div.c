#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run();
char *get_string();
void print_half_string(char *str, int len);

int main() {
    run();
    return EXIT_SUCCESS;
}

void run() {
    char *line = get_string();
    int len_line = strlen(line);
    print_half_string(line, len_line);
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

/* Функция вывода половины строки */
void print_half_string(char *str, int len) {
    char *current_symbol = str;
    for (int i = 0; i < len; i++) {
        printf("%c", *(current_symbol + i));
    }
    if (len != 1) {
        printf("\n");
        len = ceil(len * 1.0 / 2);
        print_half_string(str, len);
    }
}