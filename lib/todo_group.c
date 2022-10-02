#include "todo_group.h"

#include <stdlib.h> /* malloc, realloc */
#include <assert.h> /* assert */
#include <string.h> /* strcpy, strlen */

#define TODO_GROUP_ITEMS_INIT_SIZE 4

struct _todo_group_t {
    char *name;
    ptodo_item_t *items;

    size_t total;
    size_t capacity;
};

ptodo_group_t 
todo_group_new(void) {
    ptodo_group_t group = malloc(sizeof(todo_group_t));
    assert(group);

    group->capacity = TODO_GROUP_ITEMS_INIT_SIZE;
    group->total = 0;
    group->items = malloc(sizeof(ptodo_item_t) * group->capacity);
    assert(group->items);

    group->name = NULL;

    return group;
}

ptodo_group_t
todo_group_build(const char *const name) {
    ptodo_group_t group = todo_group_new();

    todo_group_set_name(group, name);

    return group;
}

void
todo_group_set_name(ptodo_group_t group, const char *const name) {
    group->name = malloc(sizeof(char) + strlen(name));
    assert(group->name);
    strcpy(group->name, name);
}

size_t
todo_group_get_total(ptodo_group_t group) {
    return group->total;
}

const char *
todo_group_get_name(ptodo_group_t group) {
    return group->name;
}

static void
todo_group__resize(ptodo_group_t group, size_t capacity) {
    ptodo_item_t *items = realloc(group->items, sizeof(ptodo_item_t) * capacity);
    assert(items);

    group->items = items;
    group->capacity = capacity;
}

void
todo_group_add(ptodo_group_t group, ptodo_item_t item) {
    if (group->capacity == group->total) {
        todo_group__resize(group, group->capacity * 2);
    }

    group->items[group->total++] = item;
}

ptodo_item_t
todo_group_get(ptodo_group_t group, size_t index) {
    if (index < group->total) {
        return group->items[index];
    }

    return NULL;
}

void
todo_group_set(ptodo_group_t group, size_t index, ptodo_item_t item) {
    if (index < group->total) {
        group->items[index] = item;
    }
}

void
todo_group_delete(ptodo_group_t group, size_t index) {
    if (index >= group->total) {
        return;
    }

    todo_item_free(group->items[index]);
    group->items[index] = NULL;

    for (size_t i = index; i < group->total - 1; i++) {
        group->items[i] = group->items[i + 1];
        group->items[i + 1] = NULL;
    }

    group->total--;

    if (group->total > 0 && group->total == group->capacity / 4) {
        todo_group__resize(group, group->capacity / 2);
    }
}

void
todo_group_free(ptodo_group_t group) {
    for (size_t i = 0; i < group->total; i++) {
        todo_item_free(group->items[i]);
    }

    free(group->items);
    free(group);
}