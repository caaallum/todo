TESTS = check_item check_group check_group_list check_load
check_PROGRAMS = check_item check_group check_group_list check_load

check_item_SOURCES = test_item.c $(top_builddir)/lib/todo_item.h
check_item_CFLAGS = @CHECK_CFLAGS@
check_item_LDADD = $(top_builddir)/lib/libtodo.la @CHECK_LIBS@

check_group_SOURCES = test_group.c $(top_builddir)/lib/todo_group.h
check_group_CFLAGS = @CHECK_CFLAGS@
check_group_LDADD = $(top_builddir)/lib/libtodo.la @CHECK_LIBS@

check_group_list_SOURCES = test_group_list.c $(top_builddir)/lib/todo_group_list.h
check_group_list_CFLAGS = @CHECK_CFLAGS@
check_group_list_LDADD = $(top_builddir)/lib/libtodo.la @CHECK_LIBS@

check_load_SOURCES = test_load.c $(top_builddir)/lib/todo_group_list.h
check_load_CFLAGS = @CHECK_CFLAGS@
check_load_LDADD = $(top_builddir)/lib/libtodo.la @CHECK_LIBS@