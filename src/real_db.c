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
#define DB_NAME_FILEPATH "../data-samples/task007.db"

static char *menu_command[MENU_SIZE] = {"EXIT", "SHOW", "SHOWALL", "ADD", "REMOVE"};

void run();
int get_command();
char *get_string();
void db_show_all();
void db_show();
void db_remove();

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
                db_show();
                break;
            case MENU_SHOWALL:
                db_show_all();
                break;
            case MENU_ADD:
                printf("MENU_ADD\n");
                break;
            case MENU_REMOVE:
                db_remove();
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
    sqlite3 *db;        // указатель на базу данных
    sqlite3_stmt *res;  // компилируемое выражение
    int rc = sqlite3_open(DB_NAME_FILEPATH, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        char *sql =
            "SELECT id, Name, Age, email \
            FROM Students \
            ORDER BY id";
        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        if (rc == SQLITE_OK) {
            int step = 0;
            while ((step = sqlite3_step(res)) == SQLITE_ROW) {
                printf("%d %s %d %s\n", sqlite3_column_int(res, 0), sqlite3_column_text(res, 1),
                       sqlite3_column_int(res, 2), sqlite3_column_text(res, 3));
            }
        } else {
            fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        }
    }
    sqlite3_finalize(res);  // удаляем скомпилированное выражение
    sqlite3_close(db);      // закрываем подключение
}

void db_show() {
    sqlite3 *db;        // указатель на базу данных
    sqlite3_stmt *res;  // компилируемое выражение
    int rc = sqlite3_open(DB_NAME_FILEPATH, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        char *id = get_string();
        char *sql =
            "SELECT id, Name, Age, email \
            FROM Students \
            WHERE id=?";
        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        if (rc == SQLITE_OK) {
            sqlite3_bind_text(res, 1, id, -1, SQLITE_STATIC);  // привязываем параметр
            int step = sqlite3_step(res);                      // выполняем выражение
            if (step == SQLITE_ROW) {  // если выражение успешно выполнено
                printf("%d %s %d %s\n", sqlite3_column_int(res, 0), sqlite3_column_text(res, 1),
                       sqlite3_column_int(res, 2), sqlite3_column_text(res, 3));
            } else {
                printf("NO DATA\n");
            }

        } else {
            fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        }
        free(id);
    }
    sqlite3_finalize(res);  // удаляем скомпилированное выражение
    sqlite3_close(db);
}

void db_remove() {
    sqlite3 *db;
    sqlite3_stmt *res;
    int rc = sqlite3_open(DB_NAME_FILEPATH, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        char *id = get_string();
        char *sql =
            "DELETE \
            from Students \
            WHERE id=?";
        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        if (rc == SQLITE_OK) {
            sqlite3_bind_text(res, 1, id, -1, SQLITE_STATIC);
            int step = sqlite3_step(res);
            if (step == SQLITE_ROW) {
                printf("%d %s %d %s\n", sqlite3_column_int(res, 0), sqlite3_column_text(res, 1),
                       sqlite3_column_int(res, 2), sqlite3_column_text(res, 3));
            } else {
                printf("NO DATA\n");
            }

        } else {
            fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        }
        free(id);
    }
    sqlite3_close(db);
}
