#ifndef REAL_DB_H
#define REAL_DB_H

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
#define DB_NAME_FILEPATH "./data-samples/task007.db"

static char *menu_command[MENU_SIZE] = {"EXIT", "SHOW", "SHOWALL", "ADD", "REMOVE"};

void run();
int get_command();
char *get_string();
void db_show_all();
void db_show();
void db_add();
void db_remove();
sqlite3 *db_open();
char *cat_string(char *dest, char *append);

#endif  // REAL_DB_H