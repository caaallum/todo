#include "str.h"
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen, strcpy */
#include <assert.h> /* assert */
#include <stdarg.h> /* va_list, va_start, va_and, va_copy */
#include <stdio.h> /* vsnprintf, vsprintf */

void
todo_set_string(char **dest, const char *src) {
    *dest = malloc(sizeof(char) + strlen(src));
    assert(*dest);
    strcpy(*dest, src);
}

int
vasprintf(char **out, const char *fmt, va_list args) {
  int size = 0;
  va_list tmpa;

  va_copy(tmpa, args);

  size = vsnprintf(NULL, 0, fmt, tmpa);

  va_end(tmpa);

  if (size < 0) {
    return -1;
  }

  *out = (char *) malloc(size + 1);

  if (NULL == *out) {
    return -1;
  }

  size = vsprintf(*out, fmt, args);
  return size;
}

int
asprintf(char **out, const char *fmt, ...) {
  int size = 0;
  va_list args;

  va_start(args, fmt);

  size = vasprintf(out, fmt, args);

  va_end(args);

  return size;
}