#include <stdio.h>
#include <stdlib.h>

void run();

int main() {
    run();

    return EXIT_SUCCESS;
}

void run() {
    // для просмотра использовался сайт https://inloop.github.io/sqlite-viewer/#
    int id = 7;
    char *name = "Alexandr Kuricin";
    int age = 18;
    char *email = "a.kuricin@yssu.ru";
    printf("%d %s %d %s", id, name, age, email);
}