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

item_list_t *item_list_init(void);

void item_list_add(item_list_t *list, item_t *item);

void item_list_delete(item_list_t *list, int index);

void item_list_delete_id(item_list_t *list, int id);

void item_list_free_all(item_list_t *list);

void item_list_free(item_list_t *list);

item_t *todo_item_new(void);

item_t *todo_item_build(const char *name, const char *description, const char *notes, unsigned long due, unsigned long created);

item_t *todo_item_load_one(unsigned int id);

item_list_t *todo_item_load(void);

int todo_item_save(item_t *item);

void todo_item_free(item_t *item);

#endif /* __LIB_TODO_ITEM_H */