#ifndef __LIB_TODO_STR_H
#define __LIB_TODO_STR_H

/**
 * Function: todo_set_string
 * -------------------------
 * Set string value. dest must be freed by caller
 *
 * \param dest: pointer to char array to copy to
 * \param src: char arry to copy from
 *
 */
void todo_set_string(char **dest, const char *src);

/**
 * Function: asprintf
 * ------------------
 * Allocated a formatted string. out must be freed by caller
 *
 * \param out: unintialized pointer to char array
 * \param fmt: format string
 * \param ...: args
 *
 * \retuns number of chars copied on success, -1 on fail
 */
int asprintf(char **out, const char *fmt, ...);

#endif /* __LIB_TODO_STR_H */