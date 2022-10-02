#ifndef __LIB_TODO_ITEM_H
#define __LIB_TODO_ITEM_H

typedef struct _todo_item_t todo_item_t, *ptodo_item_t;

/**
 * Create new todo item
 *
 * \return newly created todo item
 */
ptodo_item_t todo_item_new(void);

/**
 * Build todo item from existing data
 *
 * \param name 
 * \param description
 * \param notes
 * \param due
 * \param created
 *
 * \return newly created todo item
 */
ptodo_item_t todo_item_build(const char *const name, const char *const description, const char *const notes, unsigned long due, unsigned long created);

/**
 * Set name of todo item
 *
 * \param item pointer to item to set
 * \param name name to set
 */
void todo_item_set_name(ptodo_item_t item, const char *const name);

/**
 * Set desciption of todo item
 *
 * \param item pointer to item to set
 * \param desciption desciption to set
 */
void todo_item_set_description(ptodo_item_t item, const char *const desciption);

/**
 * Set notes of todo item
 *
 * \param item pointer to item to set
 * \param notes notes to set
 */
void todo_item_set_notes(ptodo_item_t item, const char *const notes);

/**
 * Set due of todo item
 *
 * \param item pointer to item to set
 * \param due due to set
 */
void todo_item_set_due(ptodo_item_t item, unsigned long due);

/**
 * Set created of todo item
 *
 * \param item pointer to item to set
 * \param created created to set
 */
void todo_item_set_created(ptodo_item_t item, unsigned long created);

/**
 * Get name of todo item
 *
 * \return name
 */
const char *todo_item_get_name(ptodo_item_t item);

/**
 * Get description of todo item
 *
 * \return description
 */
const char *todo_item_get_description(ptodo_item_t item);

/**
 * Get notes of todo item
 *
 * \return notes
 */
const char *todo_item_get_notes(ptodo_item_t item);

/**
 * Get due of todo item
 *
 * \return due
 */
unsigned long todo_item_get_due(ptodo_item_t item);

/**
 * Get created of todo item
 *
 * \return created
 */
unsigned long todo_item_get_created(ptodo_item_t item);

/**
 * Free todo item
 *
 * \param item
 */
void todo_item_free(ptodo_item_t item);

#endif/* __LIB_TODO_ITEM_H */

