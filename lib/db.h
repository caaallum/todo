#ifndef __LIB_TODO_DB_H
#define __LIB_TODO_DB_H

#include <sqlite3.h>

extern sqlite3 *todo_db;

int todo_db_init(const char *path);

void todo_db_shutdown(void);

#endif /* __LIB_TODO_DB_H */