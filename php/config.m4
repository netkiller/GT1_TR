dnl $Id$
dnl config.m4 for extension gt1

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(gt1, for gt1 support,
dnl Make sure that the comment is aligned:
dnl [  --with-gt1             Include gt1 support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(gt1, whether to enable gt1 support,
 Make sure that the comment is aligned:
[  --enable-gt1           Enable gt1 support])

if test "$PHP_GT1" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-gt1 -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/gt1.h"  # you most likely want to change this
  dnl if test -r $PHP_GT1/$SEARCH_FOR; then # path given as parameter
  dnl   GT1_DIR=$PHP_GT1
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for gt1 files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       GT1_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$GT1_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the gt1 distribution])
  dnl fi

  dnl # --with-gt1 -> add include path
  dnl PHP_ADD_INCLUDE($GT1_DIR/include)

  dnl # --with-gt1 -> check for lib and symbol presence
  dnl LIBNAME=gt1 # you may want to change this
  dnl LIBSYMBOL=gt1 # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GT1_DIR/lib, GT1_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_GT1LIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong gt1 lib version or lib not found])
  dnl ],[
  dnl   -L$GT1_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(GT1_SHARED_LIBADD)

  PHP_NEW_EXTENSION(gt1, gt1.c, $ext_shared)
fi
