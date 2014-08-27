/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_MTF_H
#define PHP_MTF_H

extern zend_module_entry mtf_module_entry;
#define phpext_mtf_ptr &mtf_module_entry

#define PHP_MTF_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_MTF_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_MTF_API __attribute__ ((visibility("default")))
#else
#	define PHP_MTF_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(mtf);
PHP_MSHUTDOWN_FUNCTION(mtf);
PHP_RINIT_FUNCTION(mtf);
PHP_RSHUTDOWN_FUNCTION(mtf);
PHP_MINFO_FUNCTION(mtf);

PHP_FUNCTION(confirm_mtf_compiled);	/* For testing, remove later. */
/*
PHP_FUNCTION(hello);
PHP_FUNCTION(myObject);
*/
PHP_METHOD(MTF, __construct);
PHP_METHOD(MTF, demo);
PHP_METHOD(MTF, login); 
PHP_METHOD(MTF, real);
PHP_METHOD(MTF, result);
PHP_METHOD(MTF, transfer);
PHP_METHOD(MTF, balance);
PHP_METHOD(MTF, change_password);
PHP_METHOD(MTF, change_flag);
PHP_METHOD(MTF, member_info);
PHP_METHOD(MTF, member_detail);

void init_class(TSRMLS_D);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(mtf)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(mtf)
*/

/* In every utility function you add that needs to use variables 
   in php_mtf_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as MTF_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define MTF_G(v) TSRMG(mtf_globals_id, zend_mtf_globals *, v)
#else
#define MTF_G(v) (mtf_globals.v)
#endif

#endif	/* PHP_MTF_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
