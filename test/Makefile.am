TESTS = check_str check_item check_db
check_PROGRAMS = check_str check_item check_db

check_str_SOURCES = check_str.c
check_str_CFLAGS = @CHECK_CFLAGS@ -I $(srcdir)/../lib
check_str_LDADD = $(top_builddir)/lib/libtodo.la @CHECK_LIBS@

check_item_SOURCES = check_item.c
check_item_CFLAGS = @CHECK_CFLAGS@ -I $(srcdir)/../lib
check_item_LDADD = $(top_builddir)/lib/libtodo.la @CHECK_LIBS@

check_db_SOURCES = check_db.c
check_db_CFLAGS = @CHECK_CFLAGS@ -I $(srcdir)/../lib
check_db_LDADD = $(top_builddir)/lib/libtodo.la @CHECK_LIBS@
