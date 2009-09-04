AC_INIT([Small Arms Ballistics],[1.3.3],[weage98@yahoo.com],[saballistics])
AC_PREREQ(2.57)
AC_CONFIG_AUX_DIR([config])
AM_CONFIG_HEADER([config.h])
AC_CONFIG_FILES([Makefile src/Makefile docs/Makefile docs/en/Makefile docs/en/index.sgml saballistics.lsm])
AM_INIT_AUTOMAKE([saballistics],[AC_PACKAGE_VERSION])
AC_PREFIX_DEFAULT([/usr/local/AC_PACKAGE_TARNAME-AC_PACKAGE_VERSION])
dnl
AC_DEFINE([COPYRIGHT],["Copyright 2005 Joshua Weage"],[Copyright string])
COPYRIGHT="Copyright 2005 Joshua Weage"
AC_SUBST([COPYRIGHT])
DATE="2 July 2005"
AC_SUBST([DATE])
LSMDATE="2JUL2005"
AC_SUBST([LSMDATE])
dnl
dnl Check for programs
dnl
AC_LANG_C
AC_PROG_CC
dnl
dnl linuxdoc is required to build documentation, so disable
dnl the documentation build if it isn't available.
dnl
AC_CHECK_PROG([linuxdoc],[linuxdoc],[true],[false])
AM_CONDITIONAL([LINUXDOC],[test x$linuxdoc = xtrue])
dnl
dnl Check for libraries
dnl
AC_CHECK_LIB([m],[main],,[AC_MSG_ERROR([math library is required])])
AC_CHECK_LIB([ncurses],[main],,[AC_MSG_ERROR([ncurses library is required])])
AC_CHECK_LIB([menu],[main],,[AC_MSG_ERROR([menu library is required])])
AC_CHECK_LIB([form],[main],,[AC_MSG_ERROR([form library is required])])
dnl
dnl Check for headers
dnl
AC_CHECK_HEADERS([malloc.h],,[AC_MSG_ERROR([malloc.h required])])
AC_HEADER_DIRENT
dnl
dnl Check for typedefs, structures and compiler characteristics
dnl
AC_TYPE_SIGNAL
dnl
dnl Check for library functions
dnl
AC_CHECK_FUNCS([sqrt])
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_MALLOC
AC_FUNC_REALLOC
dnl
dnl
AC_OUTPUT
dnl
