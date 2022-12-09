#ifndef __LIB_TODO_ITEM_H
#define __LIB_TODO_ITEM_H

typedef struct {
    char *name;
    char *description;
    char *notes;
    unsigned long due;
    unsigned long created;
} todo_item_t;

/**
 * Create new todo item
 *
 * \return newly created todo item
 */
todo_item_t *todo_item_new(void);

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
todo_item_t *todo_item_build(const char *const name,
                             const char *const description,
                             const char *const notes, unsigned long due,
                             unsigned long created);

/**
 * Set name of todo item
 *
 * \param item pointer to item to set
 * \param name name to set
 */
void todo_item_set_name(todo_item_t *item, const char *const name);

/**
 * Set desciption of todo item
 *
 * \param item pointer to item to set
 * \param desciption desciption to set
 */
void todo_item_set_description(todo_item_t *item, const char *const desciption);

/**
 * Set notes of todo item
 *
 * \param item pointer to item to set
 * \param notes notes to set
 */
void todo_item_set_notes(todo_item_t *item, const char *const notes);

/**
 * Free todo item
 *
 * \param item
 */
void todo_item_free(todo_item_t *item);

#endif /* __LIB_TODO_ITEM_H */
