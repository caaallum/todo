#ifndef __LIB_TODO_ITEM_H
#define __LIB_TODO_ITEM_H

typedef struct {
    unsigned int id;
    char *name;
    char *description;
    char *notes;
    unsigned long due;
    unsigned long created;
    unsigned int group_id;
} item_t;

typedef struct {
  item_t **items;
  int total;
  int capacity;
} item_list_t;

/**
 * Function: item_list_new
 * -----------------------
 * Creates a new empty item list struct
 *
 * \returns newly created item list
 */
item_list_t *item_list_new(void);

/**
 * Function: item_list_add
 * -----------------------
 * Adds item to item_list string
 *
 * \param list: pointer to list to struct to add to
 * \param item: pointer to item to add to list
 */
void item_list_add(item_list_t *list, item_t *item);

/**
 * Function: item_list_delete
 * --------------------------
 * Delete item from item list by array index
 *
 * \param list: pointer to item list
 * \param index: index of item to remove
 */
void item_list_delete(item_list_t *list, int index);

/**
 * Function: item_list_delete_id
 * -----------------------------
 * Delete item from item list by id
 *
 * \param list: pointer to item list
 * \param id: id of item to remove
 */
void item_list_delete_id(item_list_t *list, int id);

/**
 * Function: item_list_free_all
 * ----------------------------
 * Free all items from item list and list itself
 *
 * \param list: pointer to item list
 */
void item_list_free_all(item_list_t *list);

/**
 * Function: item_list_free_all
 * ----------------------------
 * Free item list struct
 *
 * \param list: pointer to item list
 */
void item_list_free(item_list_t *list);

/**
 * Function: item_new
 * ------------------
 * Create new empty item struct
 *
 * \returns newly created empty item struct
 */
item_t *item_new(void);

/**
 * Function: item_load_one
 * -----------------------
 * Load single item from database by id
 *
 * \param id: id of item to load
 *
 * \returns populated item struct
 */
item_t *item_load_one(unsigned int id);

/**
 * Function: item_load
 * -------------------
 * Load all items from database
 *
 * \returns list of populated items
 */
item_list_t *item_load(void);

/**
 * Function: item_save
 * -------------------
 * Save item into database
 *
 * \param item: item to save
 *
 * \returns: 0 on success, non zero on fail
 */
int item_save(item_t *item);

/**
 * F
 */
void item_free(item_t *item);

#endif /* __LIB_TODO_ITEM_H */