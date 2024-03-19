#include <sqlite3.h>
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

static int callback(void *const data, int argc, char **argv, char **azColName) {
    if (!data) {
        fprintf(stderr, "%s: ", azColName[0]);
    }

    for (int i = 0; i < argc; i++) {
        if (i == argc - 1)
            printf("%s", argv[i] ? argv[i] : "NULL");
        else
            printf("%s ", argv[i] ? argv[i] : "NULL");
    }
    printf("\n");

    return 0;
}

void run();
int get_command();
char *get_string();
void db_show_all();

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
                break;
            case MENU_SHOW:
                printf("MENU_SHOW\n");
                break;
            case MENU_SHOWALL:
                db_show_all();
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

void db_show_all() {
    sqlite3 *db;  // указатель на базу данных
    // открываем подключение к базе данных
    int rc = sqlite3_open("../data-samples/task007.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        char *zErrMsg = 0;
        const char *data = "";
        char *sql =
            "SELECT id, Name, Age, email \
            from Students \
            ORDER BY id";
        // rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
        sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
    }
    // закрываем подключение
    sqlite3_close(db);
}
