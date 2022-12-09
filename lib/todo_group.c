#include "todo_group.h"

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, realloc */
#include <string.h> /* strcpy, strlen */

#define TODO_GROUP_ITEMS_INIT_SIZE 4

todo_group_t *
todo_group_new(void) {
    todo_group_t *group = malloc(sizeof(todo_group_t));
    assert(group);

    group->capacity = TODO_GROUP_ITEMS_INIT_SIZE;
    group->total    = 0;
    group->items    = malloc(sizeof(todo_item_t *) * group->capacity);
    assert(group->items);

    group->name = NULL;

    return group;
}

todo_group_t *
todo_group_build(const char *const name) {
    todo_group_t *group = todo_group_new();

    todo_group_set_name(group, name);

    return group;
}

void
todo_group_set_name(todo_group_t *group, const char *const name) {
    group->name = malloc(sizeof(char) + strlen(name));
    assert(group->name);
    strcpy(group->name, name);
}

size_t
todo_group_get_total(todo_group_t *group) {
    return group->total;
}

const char *
todo_group_get_name(todo_group_t *group) {
    return group->name;
}

static void
todo_group__resize(todo_group_t *group, size_t capacity) {
    todo_item_t **items = realloc(group->items, sizeof(todo_item_t *) * capacity);
    assert(items);

    group->items    = items;
    group->capacity = capacity;
}

void
todo_group_add(todo_group_t *group, todo_item_t *item) {
    if (group->capacity == group->total) {
        todo_group__resize(group, group->capacity * 2);
    }

    group->items[group->total++] = item;
}

todo_item_t *
todo_group_get(todo_group_t *group, size_t index) {
    if (index < group->total) {
        return group->items[index];
    }

    return NULL;
}

void
todo_group_set(todo_group_t *group, size_t index, todo_item_t *item) {
    if (index < group->total) {
        group->items[index] = item;
    }
}

void
todo_group_delete(todo_group_t *group, size_t index) {
    if (index >= group->total) {
        return;
    }

    todo_item_free(group->items[index]);
    group->items[index] = NULL;

    for (size_t i = index; i < group->total - 1; i++) {
        group->items[i]     = group->items[i + 1];
        group->items[i + 1] = NULL;
    }

    group->total--;

    if (group->total > 0 && group->total == group->capacity / 4) {
        todo_group__resize(group, group->capacity / 2);
    }
}

void
todo_group_free(todo_group_t *group) {
    for (size_t i = 0; i < group->total; i++) {
        todo_item_free(group->items[i]);
    }

    free(group->items);
    free(group);
}
