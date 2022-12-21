AC_PREREQ([2.69])
AC_INIT([todo], [0.1.0], [callum@spei.rs])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([1.9.6 -Wall -Werror dist-bzip2])
AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

AM_PROG_AR
AC_PROG_CC

AC_PROG_INSTALL
LT_INIT

PKG_CHECK_MODULES([SQLITE], [sqlite3])
PKG_CHECK_MODULES([CHECK], [check])

AC_ARG_ENABLE(debug,
    AS_HELP_STRING([--enable-debug], [Use debug configuration and output settings]),
    AC_DEFINE([DEBUG], [], [Show extra output]),
    AC_DEFINE([RELEASE], [], [Release build])
)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile lib/Makefile test/Makefile])

AC_OUTPUT
