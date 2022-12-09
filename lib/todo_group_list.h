#ifndef __LIB_TODO_GROUP_LIST_H
#define __LIB_TODO_GROUP_LIST_H

#include "todo_group.h"

typedef struct _todo_group_list_t todo_group_list_t;

/**
 * Load groups from database
 * 
 * \return populated group_list
 */
todo_group_list_t *todo_group_list_load_all(const char *const xml);

/**
 * Init group list
 * 
 * \return newly created group list
 */
todo_group_list_t *todo_group_list_new(void);

/**
 * Get number of groups in list
 * 
 * \param group_list
 * 
 * \return size_t
 */
size_t todo_group_list_get_total(todo_group_list_t *group_list);

/**
 * Add group to list
 * 
 * \param group_list
 * \param group
 */
void todo_group_list_add(todo_group_list_t *group_list, todo_group_t *group);

/**
 * Set group in list
 * 
 * \param group_list
 * \param index
 * \param group
 */
void todo_group_list_set(todo_group_list_t *group_list, size_t index, todo_group_t *group);

/**
 * Get group in list
 * 
 * \param group_list
 * \param index
 * 
 * \return group
 */
todo_group_t *todo_group_list_get(todo_group_list_t *group_list, size_t index);

/**
 * Delete group in list
 * 
 * \param group_list
 * \param index
 */
void todo_group_list_delete(todo_group_list_t *group_list, size_t index);

/**
 * Free group_list
 * 
 * \param group_list
 */
void todo_group_list_free(todo_group_list_t *group_list);

#endif /* __LIB_TODO_GROUP_LIST_H */
