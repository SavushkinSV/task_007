#include "real_db.h"

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
                db_add();
                break;
            case MENU_REMOVE:
                db_remove();
                break;
            default:
                break;
        }
    }
}

/* Функция получения команды */
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

/* Функция вывода всех строк в таблице */
void db_show_all() {
    sqlite3 *db = db_open();
    sqlite3_stmt *res;
    if (db != NULL) {
        char *sql =
            "SELECT id, Name, Age, email \
            FROM Students \
            ORDER BY id";
        int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        if (rc == SQLITE_OK) {
            int step = 0;
            while ((step = sqlite3_step(res)) == SQLITE_ROW) {
                printf("%d %s %d %s\n", sqlite3_column_int(res, 0), sqlite3_column_text(res, 1),
                       sqlite3_column_int(res, 2), sqlite3_column_text(res, 3));
            }
        } else {
            fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(res);
        sqlite3_close(db);
    }
}

/* Функция отображения строки по id */
void db_show() {
    sqlite3 *db = db_open();
    sqlite3_stmt *res;  // компилируемое выражение
    if (db != NULL) {
        char *id = get_string();
        char *sql =
            "SELECT id, Name, Age, email \
            FROM Students \
            WHERE id=?";
        int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
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
        sqlite3_finalize(res);
        sqlite3_close(db);
    }
}

/* Функция удаления строки по id */
void db_remove() {
    sqlite3 *db = db_open();
    sqlite3_stmt *res;
    if (db != NULL) {
        char *id = get_string();
        char *sql =
            "DELETE \
            FROM Students \
            WHERE id=?";
        int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        if (rc == SQLITE_OK) {
            sqlite3_bind_text(res, 1, id, -1, SQLITE_STATIC);
            sqlite3_step(res);
        } else {
            fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        }
        free(id);
        sqlite3_finalize(res);
        sqlite3_close(db);
    }
}

/* Функция открытия файла с базой данных */
sqlite3 *db_open() {
    sqlite3 *db = NULL;
    int rc = sqlite3_open(DB_NAME_FILEPATH, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    return db;
}

/* Функция добавления новой строки */
void db_add() {
    sqlite3 *db = db_open();
    sqlite3_stmt *res;
    if (db != NULL) {
        char *line = get_string();
        char *name = NULL;
        char *age = NULL;
        char *email = NULL;
        char *token = strtok(line, " ");
        while (token != NULL) {
            if (*token >= '0' && *token <= '9') {
                age = (char *)malloc((strlen(token) + 1) * sizeof(char));
                strcpy(age, token);
                token = strtok(NULL, " ");
                email = (char *)malloc((strlen(token) + 1) * sizeof(char));
                strcpy(email, token);
            } else {
                name = cat_string(name, token);
            }
            token = strtok(NULL, " ");
        }
        char *sql =
            "INSERT \
            INTO Students (Name, Age, email) \
            VALUES (?, ?, ?)";
        int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        if (rc == SQLITE_OK) {
            sqlite3_bind_text(res, 1, name, -1, SQLITE_STATIC);
            sqlite3_bind_text(res, 2, age, -1, SQLITE_STATIC);
            sqlite3_bind_text(res, 3, email, -1, SQLITE_STATIC);
            sqlite3_step(res);
        } else {
            fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        }
        free(line);
        free(name);
        free(age);
        free(email);
        sqlite3_finalize(res);
        sqlite3_close(db);
    }
}

/* Функция конкатенации строки. Возвращает новый указатель */
char *cat_string(char *dest, char *append) {
    int len_append = strlen(append);
    if (dest != NULL) {
        int len_dest = strlen(dest);
        dest = realloc(dest, (len_dest + len_append + 2) * sizeof(char));
        strcat(dest, " ");
        strcat(dest, append);
    } else {
        dest = (char *)malloc((len_append + 2) * sizeof(char));
        strcpy(dest, append);
    }

    return dest;
}