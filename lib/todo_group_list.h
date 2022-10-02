#ifndef __LIB_TODO_GROUP_LIST_H
#define __LIB_TODO_GROUP_LIST_H

#include "todo_group.h"

typedef struct _todo_group_list_t todo_group_list_t, *ptodo_group_list_t;

/**
 * Load groups from database
 * 
 * \return populated group_list
 */
ptodo_group_list_t todo_group_list_load_all(const char *const xml);

/**
 * Init group list
 * 
 * \return newly created group list
 */
ptodo_group_list_t todo_group_list_new(void);

/**
 * Get number of groups in list
 * 
 * \param group_list
 * 
 * \return size_t
 */
size_t todo_group_list_get_total(ptodo_group_list_t group_list);

/**
 * Add group to list
 * 
 * \param group_list
 * \param group
 */
void todo_group_list_add(ptodo_group_list_t group_list, ptodo_group_t group);

/**
 * Set group in list
 * 
 * \param group_list
 * \param index
 * \param group
 */
void todo_group_list_set(ptodo_group_list_t group_list, size_t index, ptodo_group_t group);

/**
 * Get group in list
 * 
 * \param group_list
 * \param index
 * 
 * \return group
 */
ptodo_group_t todo_group_list_get(ptodo_group_list_t group_list, size_t index);

/**
 * Delete group in list
 * 
 * \param group_list
 * \param index
 */
void todo_group_list_delete(ptodo_group_list_t group_list, size_t index);

/**
 * Free group_list
 * 
 * \param group_list
 */
void todo_group_list_free(ptodo_group_list_t group_list);

#endif/* __LIB_TODO_GROUP_LIST_H */