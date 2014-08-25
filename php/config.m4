dnl $Id$
dnl config.m4 for extension mtf

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(mtf, for mtf support,
dnl Make sure that the comment is aligned:
dnl [  --with-mtf             Include mtf support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(mtf, whether to enable mtf support,
 Make sure that the comment is aligned:
[  --enable-mtf           Enable mtf support])

if test "$PHP_MTF" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-mtf -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/mtf.h"  # you most likely want to change this
  dnl if test -r $PHP_MTF/$SEARCH_FOR; then # path given as parameter
  dnl   MTF_DIR=$PHP_MTF
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for mtf files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MTF_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MTF_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the mtf distribution])
  dnl fi

  dnl if ! test -x "/usr/bin/xml2-config"; then
  dnl	AC_MSG_ERROR(Cannot find libxml2)
  dnl fi

  dnl # --with-mtf -> add include path
  dnl PHP_ADD_INCLUDE($MTF_DIR/include)

  dnl # --with-mtf -> check for lib and symbol presence
  dnl LIBNAME=mtf # you may want to change this
  dnl LIBSYMBOL=mtf # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MTF_DIR/lib, MTF_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MTFLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong mtf lib version or lib not found])
  dnl ],[
  dnl   -L$MTF_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MTF_SHARED_LIBADD)
  XML_LIBS=$(xml2-config --libs)
  XML_INCS=$(xml2-config --cflags)
  PHP_EVAL_LIBLINE($XML_LIBS, MTF_SHARED_LIBADD)
  PHP_EVAL_INCLINE($XML_INCS)

  PHP_NEW_EXTENSION(mtf, mtf.c, $ext_shared)
fi
