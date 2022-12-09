#ifndef __LIB_TODO_GROUP_H
#define __LIB_TODO_GROUP_H

#include <stddef.h> /* size_t */

#include "todo_item.h"

typedef struct {
    char *name;
    todo_item_t **items;

    size_t total;
    size_t capacity;
} todo_group_t;

/**
 * Create new group
 *
 * \return newly created group
 */
todo_group_t *todo_group_new(void);

/**
 * Build group from existing data
 *
 * \return newly created group
 */
todo_group_t *todo_group_build(const char *const name);

/**
 * Set name of todo group
 *
 * \param group group to set
 * \param name to set
 */
void todo_group_set_name(todo_group_t *group, const char *const name);

/**
 * Get number of items in group
 * 
 * \param group
 * 
 * \return size_t
 */
size_t todo_group_get_total(todo_group_t *group);

/**
 * Add item to group
 * 
 * \param group
 * \param item
 */
void todo_group_add(todo_group_t *group, todo_item_t *item);

/**
 * Set item in group
 * 
 * \param group
 * \param index
 * \param item
 */
void todo_group_set(todo_group_t *group, size_t index, todo_item_t *item);

/**
 * Get item from group
 * 
 * \param group
 * \param index
 */
todo_item_t *todo_group_get(todo_group_t *group, size_t index);

/**
 * Delete item from group
 * 
 * \param group
 * \param index
 */
void todo_group_delete(todo_group_t *group, size_t index);

/**
 * Free group
 * 
 * \param group
 */
void todo_group_free(todo_group_t *group);

#endif /* __LIB_TODO_GROUP_H */
