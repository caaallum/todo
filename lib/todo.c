#include "todo.h"
#include "db.h"

#define TODO_DB_LOCATION "~/.local/todo/todo.db"
#define TODO_DB_LOCAL "todo.db"

int
todo_init(unsigned int flags) {
    int rc;


    if (flags == TODO_FLAGS_NONE) {
      rc = todo_db_init(TODO_DB_LOCATION);
    }

    if (flags & TODO_FLAGS_MEMORY) {
      rc = todo_db_init(":memory:");
    }

    if (flags & TODO_FLAGS_LOCAL) {
      rc = todo_db_init(TODO_DB_LOCAL);
    }

    return rc;
}

void
todo_shutdown(void) {
  todo_db_shutdown();
}