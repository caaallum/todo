#ifndef __LIB_TODO_DB_H
#define __LIB_TODO_DB_H

#include <sqlite3.h>

extern sqlite3 *todo_db;

/**
 * Function: todo_db_init
 * ----------------------
 * Init database for todo instance
 *
 * \param path: path of database file
 *
 * \returns 0 on success, non zero on fail
 */
int todo_db_init(const char *path);

/**
 * Function: todo_db_shutdown
 * -------------------------
 * Shutdown database instance
 */
void todo_db_shutdown(void);

#endif /* __LIB_TODO_DB_H */
