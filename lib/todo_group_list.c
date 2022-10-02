#include "todo_group_list.h"

#include <stdlib.h> /* malloc, realloc */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */

#include <libxml/parser.h>
#include <libxml/tree.h>

#define TODO_GROUP_LIST_ITEMS_INIT_SIZE 4

struct _todo_group_list_t {
    ptodo_group_t *groups;

    size_t total;
    size_t capacity;
};



ptodo_group_list_t
todo_group_list_load_all(void) {
    static char filename[] = "load_all.xml";
    ptodo_group_list_t group_list = todo_group_list_new();
    
    xmlDocPtr doc = NULL;
    xmlNodePtr root_element = NULL, child_element = NULL, cur_node = NULL;

    doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        return group_list;
    }

    root_element = xmlDocGetRootElement(doc);
    child_element = root_element->children;
    for (cur_node = child_element; cur_node; cur_node = cur_node->next) {
        if (xmlStrcmp(cur_node->name, BAD_CAST "group") == 0) {
            ptodo_group_t group = todo_group_new();

            xmlNodePtr group_element = NULL, group_current = NULL;

            group_element = cur_node->children;
            for (group_current = group_element; group_current; group_current = group_current->next) {
                if (xmlStrcmp(group_current->name, BAD_CAST "name") == 0) {
                    xmlChar *name = xmlNodeGetContent(group_current);
                    todo_group_set_name(group, (const char *) name);
                    xmlFree(name);
                }
                if (xmlStrcmp(group_current->name, BAD_CAST "items") == 0) {
                    
                }
            }

            todo_group_list_add(group_list, group);
        }

    }

    xmlFreeDoc(doc);

    return group_list;
}

ptodo_group_list_t
todo_group_list_new(void) {
    ptodo_group_list_t group_list = malloc(sizeof(todo_group_list_t));
    assert(group_list);

    group_list->capacity = TODO_GROUP_LIST_ITEMS_INIT_SIZE;
    group_list->total = 0;
    group_list->groups = malloc(sizeof(ptodo_group_t) * group_list->capacity);
    assert(group_list->groups);

    return group_list;
}

size_t
todo_group_list_get_total(ptodo_group_list_t group_list) {
    return group_list->total;
}

static void
todo_group_list__resize(ptodo_group_list_t group_list, size_t capacity) {
    ptodo_group_t *groups = realloc(group_list->groups, sizeof(ptodo_group_t) * capacity);
    assert(groups);

    group_list->groups = groups;
    group_list->capacity = capacity;
}

void
todo_group_list_add(ptodo_group_list_t group_list, ptodo_group_t group) {
    if (group_list->capacity == group_list->total) {
        todo_group_list__resize(group_list, group_list->capacity * 2);
    }

    group_list->groups[group_list->total++] = group;
}

void
todo_group_list_set(ptodo_group_list_t group_list, size_t index, ptodo_group_t group) {
    if (index < group_list->total) {
        group_list->groups[index] = group;
    }
}

ptodo_group_t
todo_group_list_get(ptodo_group_list_t group_list, size_t index) {
    if (index < group_list->total) {
        return group_list->groups[index];
    }

    return NULL;
}

void 
todo_group_list_delete(ptodo_group_list_t group_list, size_t index) {
    if (index >= group_list->total) {
        return;
    }

    todo_group_free(group_list->groups[index]);
    group_list->groups[index] = NULL;

    for(size_t i = index; i < group_list->total - 1; i++) {
        group_list->groups[i] = group_list->groups[i + 1];
        group_list->groups[i + 1] = NULL;
    }

    group_list->total--;

    if (group_list->total > 0 && group_list->total == group_list->capacity / 4) {
        todo_group_list__resize(group_list, group_list->capacity / 2);
    }
}

void
todo_group_list_free(ptodo_group_list_t group_list) {
    for (size_t i = 0; i < group_list->total; i++) {
        todo_group_free(group_list->groups[i]);
    }

    free(group_list->groups);
    free(group_list);
}
