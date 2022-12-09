#include "todo_item.h"

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen, strcpy */

todo_item_t *
todo_item_new(void) {
    todo_item_t *item = malloc(sizeof(todo_item_t));
    assert(item);

    item->name        = NULL;
    item->description = NULL;
    item->notes       = NULL;
    item->due         = 0;
    item->created     = 0;

    return item;
}

todo_item_t *
todo_item_build(const char *const name,
                const char *const description,
                const char *const notes, unsigned long due,
                unsigned long created) {
    todo_item_t *item = malloc(sizeof(todo_item_t));
    assert(item);

    todo_item_set_name(item, name);
    todo_item_set_description(item, description);
    todo_item_set_notes(item, notes);
    item->due     = due;
    item->created = created;

    return item;
}

void
todo_item_set_name(todo_item_t *item, const char *const name) {
    item->name = malloc(sizeof(char) + strlen(name));
    assert(item->name);
    strcpy(item->name, name);
}

void
todo_item_set_description(todo_item_t *item,
                          const char *const description) {
    item->description = malloc(sizeof(char) + strlen(description));
    assert(item->description);
    strcpy(item->description, description);
}

void
todo_item_set_notes(todo_item_t *item, const char *const notes) {
    item->notes = malloc(sizeof(char) + strlen(notes));
    assert(item->notes);
    strcpy(item->notes, notes);
}

void
todo_item_free(todo_item_t *item) {
    free(item->name);
    free(item->description);
    free(item->notes);

    free(item);
}
