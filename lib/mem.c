#include "mem.h"
#include <stdlib.h> /* free */

void
todo_free(void *obj) {
  if (obj != NULL) {
    free(obj);
  }
}