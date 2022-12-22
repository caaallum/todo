#ifndef __LIB_TODO_GROUP_H
#define __LIB_TODO_GROUP_H

#include "item.h"

typedef struct {
    unsigned int id;
    char *name;
    item_list_t *items;
} group_t;

typedef struct {
  group_t **groups;
  int total;
  int capacity;
} group_list_t;

group_list_t *group_list_new(void);

void group_list_add(group_list_t *list, group_t *group);

void group_list_delete(group_list_t *list, int index);

void group_list_delete_id(group_list_t *list, int id);

void group_list_free_all(group_list_t *list);

void group_list_free(group_list_t *list);

group_t *group_new(void);

void group_free(group_t *group);

#endif /* __LIB_TODO_GROUP_H */
