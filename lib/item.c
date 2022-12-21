#include "item.h"
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <stdio.h> /* fprintf */
#include <string.h> /* strcmp */
#include "str.h"
#include "mem.h"
#include "db.h"

item_list_t *
item_list_init(void) {
    item_list_t *list = malloc(sizeof(item_list_t));
    assert(list);

    list->capacity = 4;
    list->total = 0;
    list->items = malloc(sizeof(item_t *) * list->capacity);
    assert(list->items);

    return list;
}

static void
item_list_resize(item_list_t *list, int capacity) {
    item_t **items = realloc(list->items, sizeof(item_t *) * capacity);
    assert(items);

    list->items = items;
    list->capacity = capacity;
}

void
item_list_add(item_list_t *list, item_t *item) {
    assert(list);
    assert(item);

    if (list->capacity == list->total) {
        item_list_resize(list, list->capacity * 2);
    }

    list->items[list->total++] = item;
}

void
item_list_delete(item_list_t *list, int index) {
    assert(list);

    if (index < 0 || index >= list->total) {
        return;
    }

    item_free(list->items[index]);
    list->items[index] = NULL;

    for (int i = index; i < list->total - 1; i++) {
        list->items[i] = list->items[i + 1];
        list->items[i + 1] = NULL;
    }

    list->total--;

    if (list->total > 0 && list->total == list->capacity / 4) {
        item_list_resize(list, list->capacity / 2);
    }
}

void
item_list_delete_id(item_list_t *list, int id) {
    for (int i = 0; i < list->total; i++) {
        item_t *item = list->items[i];
        if (item->id == id) {
            item_list_delete(list, i);
        }
    }
}

void
item_list_free(item_list_t *list) {
    free(list->items);
    free(list);
}

void
item_list_free_all(item_list_t *list) {
    for (int i = 0; i < list->total; i++) {
        item_free(list->items[i]);
    }
    item_list_free(list);
}

item_t *
item_new(void) {
    item_t *item = malloc(sizeof(item_t));
    assert(item);

    item->name = NULL;
    item->description = NULL;
    item->notes = NULL;
    item->due = 0;
    item->created = 0;
    item->group_id = 0;

    return item;
}

item_t *
item_build(const char *name, const char *description, const char *notes, unsigned long due, unsigned long created) {
    item_t *item = item_new();

    todo_set_string(&item->name, name);
    todo_set_string(&item->description, description);
    todo_set_string(&item->notes, notes);
    item->due = due;
    item->created = created;

    return item;
}

int
item_save(item_t *item) {
    static char item_save_format[] = "INSERT INTO item(name, description, notes, due, created, groupid) VALUES('%s', '%s', '%s', %ld, %ld, %d);";
    char *sql = NULL;
    char *err_msg;
    int rc;

    asprintf(&sql, item_save_format, item->name, item->description, item->notes, item->due, item->created, item->group_id);

    assert(sql);

    rc = sqlite3_exec(todo_db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to save item: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    item->id = sqlite3_last_insert_rowid(todo_db);

    free(sql);

    return rc;
}

int _item_load(void *udp, int c_num, char **c_vals, char **c_names) {
    item_list_t *list = (item_list_t *)udp;

    item_t *item = item_new();

    for (int i = 0; i < c_num; i++) {
        if (strcmp(c_names[i], "id") == 0) {
            item->id = (unsigned int)strtol(c_vals[i], (char **) NULL, 10);
        }

        if (strcmp(c_names[i], "name") == 0) {
            todo_set_string(&item->name, c_vals[i]);
        }

        if (strcmp(c_names[i], "description") == 0) {
            todo_set_string(&item->description, c_vals[i]);
        }

        if (strcmp(c_names[i], "notes") == 0) {
            todo_set_string(&item->notes, c_vals[i]);
        }

        if (strcmp(c_names[i], "due") == 0) {
            item->due = strtol(c_vals[i], (char **) NULL, 10);
        }

        if (strcmp(c_names[i], "created") == 0) {
            item->created = strtol(c_vals[i], (char **) NULL, 10);
        }

        if (strcmp(c_names[i], "group_id") == 0) {
            item->group_id = (unsigned int)strtol(c_vals[i], (char **) NULL, 10);
        }
    }
    item_list_add(list, item);
    return 0;
}

item_list_t *
item_load(void) {
    static char sql[] = "SELECT * FROM item;";
    int rc;
    char *err_msg;
    item_list_t *list = item_list_init();

    rc = sqlite3_exec(todo_db, sql, _item_load, list, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to query item %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    return list;
}

item_t *
item_load_one(unsigned int id) {
    char *sql;
    int rc;
    char *err_msg;
    item_list_t *list = item_list_init();
    item_t *item = NULL;

    asprintf(&sql, "SELECT * FROM item WHERE id = %d", id);
    assert(sql);

    rc = sqlite3_exec(todo_db, sql, _item_load, list, &err_msg);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to query item %s\n", err_msg);
      sqlite3_free(err_msg);
      item_list_free(list);
      free(sql);
      return NULL;
    }

    free(sql);

    item = list->items[0];

    item_list_free(list);

    return item;
}

void
item_free(item_t *item) {
    free(item->name);
    free(item->description);
    free(item->notes);
    free(item);
}