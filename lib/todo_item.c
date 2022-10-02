#include "todo_item.h"

#include <string.h> /* strlen, strcpy */ 
#include <assert.h> /* assert */ 
#include <stdlib.h> /* malloc */

struct _todo_item_t {
    char *name;
    char *description;
    char *notes;
    unsigned long due;
    unsigned long created;
};

ptodo_item_t 
todo_item_new(void) {
    ptodo_item_t item = malloc(sizeof(todo_item_t));
    assert(item);

    item->name = NULL;
    item->description = NULL;
    item->notes = NULL;
    item->due = 0;
    item->created = 0;

    return item;
}

ptodo_item_t
todo_item_build(const char *const name, const char *const description, const char *const notes, unsigned long due, unsigned long created) {
    ptodo_item_t item = malloc(sizeof(todo_item_t));
    assert(item);

    todo_item_set_name(item, name);
    todo_item_set_description(item, description);
    todo_item_set_notes(item, notes);
    todo_item_set_due(item, due);
    todo_item_set_created(item, created);

    return item;
}

void
todo_item_set_name(ptodo_item_t item, const char *const name) {
    item->name = malloc(sizeof(char) + strlen(name));
    assert(item->name);
    strcpy(item->name, name);
}

void
todo_item_set_description(ptodo_item_t item, const char *const description) {
    item->description = malloc(sizeof(char) + strlen(description));
    assert(item->description);
    strcpy(item->description, description);
}

void
todo_item_set_notes(ptodo_item_t item, const char *const notes) {
    item->notes = malloc(sizeof(char) + strlen(notes));
    assert(item->notes);
    strcpy(item->notes, notes);
}

void 
todo_item_set_due(ptodo_item_t item, unsigned long due) {
    item->due = due;
}

void
todo_item_set_created(ptodo_item_t item, unsigned long created) {
    item->created = created;
}

const char *
todo_item_get_name(ptodo_item_t item) {
    return item->name;
}

const char *
todo_item_get_description(ptodo_item_t item) {
    return item->description;
}

const char *
todo_item_get_notes(ptodo_item_t item) {
    return item->notes;
}

unsigned long 
todo_item_get_due(ptodo_item_t item) {
    return item->due;
}

unsigned long
todo_item_get_created(ptodo_item_t item) {
    return item->created;
}

void
todo_item_free(ptodo_item_t item) {
    free(item->name);
    free(item->description);
    free(item->notes);

    free(item);
}
