#include "db.h"
#include <stdlib.h>
#include <stdio.h>

sqlite3 *todo_db = NULL;

int
todo_db_init(const char *path) {
    int rc = -1;
    char *err_msg = 0;
    static char group_create[] = "CREATE TABLE IF NOT EXISTS todo_group (id INTEGER PRIMARY KEY, name TEXT);";
    static char item_create[] = "CREATE TABLE IF NOT EXISTS todo_item (id INTEGER PRIMARY KEY, name TEXT, description TEXT, notes TEXT, due INTEGER, created INTEGER, groupid INTEGER, FOREIGN KEY(groupid) REFERENCES todo_group(id));";

    rc = sqlite3_open(path, &todo_db);

    if (rc != SQLITE_OK) {
        return 1;
    }

    /* Init tables */
    rc = sqlite3_exec(todo_db, group_create, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to create table group: %s\n", err_msg);
      sqlite3_free(err_msg);
      return 1;
    }

    rc = sqlite3_exec(todo_db, item_create, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to create table item: %s\n", err_msg);
      sqlite3_free(err_msg);
      return 1;
    }

    return 0;
}

void
todo_db_shutdown(void) {
    sqlite3_close(todo_db);
}