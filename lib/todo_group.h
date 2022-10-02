#ifndef __LIB_TODO_GROUP_H
#define __LIB_TODO_GROUP_H

#include <stddef.h> /* size_t */

#include "todo_item.h"

typedef struct _todo_group_t todo_group_t, *ptodo_group_t;

/**
 * Create new group
 *
 * \return newly created group
 */
ptodo_group_t todo_group_new(void);

/**
 * Build group from existing data
 *
 * \return newly created group
 */
ptodo_group_t todo_group_build(const char *const name);

/**
 * Set name of todo group
 *
 * \param group group to set
 * \param name to set
 */
void todo_group_set_name(ptodo_group_t group, const char *const name);

/**
 * Get number of items in group
 * 
 * \param group
 * 
 * \return size_t
 */
size_t todo_group_get_total(ptodo_group_t group);

/**
 * Get name of todo group
 *
 * \param group
 * 
 * \return name
 */
const char *todo_group_get_name(ptodo_group_t group);

/**
 * Add item to group
 * 
 * \param group
 * \param item
 */
void todo_group_add(ptodo_group_t group, ptodo_item_t item);

/**
 * Set item in group
 * 
 * \param group
 * \param index
 * \param item
 */
void todo_group_set(ptodo_group_t group, size_t index, ptodo_item_t item);

/**
 * Get item from group
 * 
 * \param group
 * \param index
 */
ptodo_item_t todo_group_get(ptodo_group_t group, size_t index);

/**
 * Delete item from group
 * 
 * \param group
 * \param index
 */
void todo_group_delete(ptodo_group_t group, size_t index);

/**
 * Free group
 * 
 * \param group
 */
void todo_group_free(ptodo_group_t group);

#endif/* __LIB_TODO_GROUP_H */
