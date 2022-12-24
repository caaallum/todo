#include "group.h"
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include "mem.h"

group_list_t *
group_list_new(void) {
    group_list_t *list = malloc(sizeof(group_list_t));
    assert(list);

    list->capacity = 4;
    list->total = 0;
    list->groups = malloc(sizeof(group_t *) * list->capacity);
    assert(list->groups);

    return list;
}

static void
group_list_resize(group_list_t *list, int capacity) {
    group_t **groups = realloc(list->groups, sizeof(group_t *) * capacity);
    assert(groups);

    list->groups = groups;
    list->capacity = capacity;
}

void
group_list_add(group_list_t *list, group_t *group) {
    assert(list);
    assert(group);

    if (list->capacity == list->total) {
        group_list_resize(list, list->capacity * 2);
    }

    list->groups[list->total++] = group;
}

void
group_list_delete(group_list_t *list, int index) {
    assert(list);

    if (index < 0 || index >= list->total) {
        return;
    }

    group_free(list->groups[index]);
    list->groups[index] = NULL;

    for (int i = index; i < list->total; i++) {
        list->groups[i] = list->groups[i + 1];
        list->groups[i + 1] = NULL;
    }

    list->total--;

    if (list->total > 0 && list->total == list->capacity / 4) {
        group_list_resize(list, list->capacity / 2);
    }
}

void
group_list_delete_id(group_list_t *list, int id) {
    for (int i = 0; i < list->total; i++) {
        group_t *group = list->groups[i];
        if (group->id == id) {
            group_list_delete(list, i);
        }
    }
}

void
group_list_free(group_list_t *list) {
    free(list->groups);
    free(list);
}

void
group_list_free_all(group_list_t *list) {
    for (int i = 0; i < list->total; i++) {
        group_free(list->groups[i]);
    }
    group_list_free(list);
}

group_t *
group_new(void) {
    group_t *group = malloc(sizeof(group_t));
    assert(group);
    group->id = 0;
    group->name = NULL;
    group->items = item_list_new();

    return group;
}

int
group_save(group_t *group) {
    static char group_save_format[] = "INSERT INTO todo_group(name) VALUES('%s');";
    char *sql = NULL;
    char *err_msg;
    int rc;

    asprintf(&sql, group_save_format, group->name);
}

void
group_free(group_t *group) {
    item_list_free_all(group->items);
    todo_free(group->name);
    free(group);
}
