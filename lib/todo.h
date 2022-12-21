#ifndef __LIB_TODO_H
#define __LIB_TODO_H

#include "group.h"
#include "item.h"

#define TODO_FLAGS_NONE 0
#define TODO_FLAGS_MEMORY 1 << 1
#define TODO_FLAGS_LOCAL 1 << 2

int todo_init(unsigned int flags);

void todo_shutdown(void);

#endif /* __LIB_TODO_H */