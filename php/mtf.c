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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_mtf.h"

#include "../curl.h"
#include "../protocol.h"

/* If you declare any globals in php_mtf.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(mtf)
*/

/* True global resources - no need for thread safety here */
static int le_mtf;
zend_class_entry *object;

/* {{{ mtf_functions[]
 *
 * Every user visible function must have an entry in mtf_functions[].
 */
const zend_function_entry mtf_functions[] = {
	PHP_FE(confirm_mtf_compiled,	NULL)		/* For testing, remove later. */
/*	
	PHP_FE(hello,	NULL)
	PHP_FE(myObject,	NULL)
*/
	PHP_FE_END	/* Must be the last line in mtf_functions[] */
};

/* }}} */

const zend_function_entry mtf_class_methods[] = {
	PHP_ME(MTF, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(MTF, demo, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MTF, login, NULL, ZEND_ACC_PUBLIC) 
	PHP_ME(MTF, real, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MTF, result, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MTF, transfer, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MTF, balance, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MTF, change_password, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MTF, change_flag, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MTF, member_info, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MTF, member_detail, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

/* {{{ mtf_module_entry
 */
zend_module_entry mtf_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"mtf",
	mtf_functions,
	PHP_MINIT(mtf),
	PHP_MSHUTDOWN(mtf),
	PHP_RINIT(mtf),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(mtf),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(mtf),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_MTF_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

//#ifdef COMPILE_DL_MTF
ZEND_GET_MODULE(mtf)
//#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini */

PHP_INI_BEGIN()
    //STD_PHP_INI_ENTRY("mtf.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_mtf_globals, mtf_globals)
    //STD_PHP_INI_ENTRY("mtf.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_mtf_globals, mtf_globals)
	PHP_INI_ENTRY("test", "aaaaaaaaaaaaaaaaaaa", PHP_INI_ALL,  NULL)
	PHP_INI_ENTRY("mtf.url", "http://localhost", PHP_INI_ALL,  NULL)
	PHP_INI_ENTRY("mtf.user", "", PHP_INI_ALL,  NULL)
	PHP_INI_ENTRY("mtf.password", "", PHP_INI_ALL,  NULL)
PHP_INI_END()

/* }}} */

/* {{{ php_mtf_init_globals
 */
/* Uncomment this function if you have INI entries 
static void php_mtf_init_globals(zend_mtf_globals *mtf_globals)
{
	mtf_globals->global_value = 0;
	mtf_globals->global_string = NULL;
}
*/
/* }}} */

void init_class(TSRMLS_D) {
	zend_class_entry ce;
 
	INIT_CLASS_ENTRY(ce, "MTF", mtf_class_methods);
	//INIT_CLASS_ENTRY(ce, "MTF", Null);
	object = zend_register_internal_class(&ce TSRMLS_CC);
 
	zend_declare_property_string(object, "debug", strlen("debug"), "", ZEND_ACC_PUBLIC TSRMLS_CC);	
	zend_declare_property_string(object, "session", strlen("session"), "", ZEND_ACC_PUBLIC TSRMLS_CC);
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(mtf)
{
	/* If you have INI entries, uncomment these lines */
	REGISTER_INI_ENTRIES();
	
	init_class(TSRMLS_C);
	
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(mtf)
{
	/* uncomment this line if you have INI entries */
	UNREGISTER_INI_ENTRIES();
	
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(mtf)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(mtf)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(mtf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "mtf support", "enabled");
	php_info_print_table_row(2, "mtf.author", "Neo Chan<netkiller@msn.com>");
	php_info_print_table_row(2, "mtf.url", INI_STR("mtf.url"));
	php_info_print_table_row(2, "mtf.user", INI_STR("mtf.user"));	
	php_info_print_table_row(2, "mtf.password", INI_STR("mtf.password"));	
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_mtf_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_mtf_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "mtf", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/
/*
PHP_FUNCTION(hello) {
    php_printf("Hello\n");
}

PHP_FUNCTION(myObject) {
    object_init(return_value);

    // add a couple of properties
    zend_update_property_string(NULL, return_value, "name", strlen("name"), "yig" TSRMLS_CC);
    zend_update_property_long(NULL, return_value, "worshippers", strlen("worshippers"), 4 TSRMLS_CC);
}
*/

PHP_METHOD(MTF, __construct) {
	// TODO     
	//php_printf("Hello\n");  
	char *str="2014-08-27";
	zend_update_property_string(object, getThis(), "version", strlen("version"), str TSRMLS_CC);
	//zend_update_property_string(object, getThis(), "session", strlen("session"), session TSRMLS_CC);
}

PHP_METHOD(MTF, demo) {
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}
	
	char *xmlpro = 	protocol_demo(arg);
	char *url;
	asprintf(&url, "%s/add_demo_member.ucs", INI_STR("mtf.url"));		
	char *xml = conn(url, xmlpro);
	char *debug = NULL;
	asprintf(&debug, "%s?%s",url, xmlpro);
	zend_update_property_string(object, getThis(), "debug", strlen("debug"), debug TSRMLS_CC);
	
	len = spprintf(&strg, 0, "%s", xml);
	RETURN_STRINGL(strg, len, 0);
}

PHP_METHOD(MTF, login) {
	char *url = INI_STR("mtf.url");
	char *user = NULL;
	int user_len;
	
	char *password = NULL;
	int password_len;
	
	int len;
	char *strg;
	
	if(ZEND_NUM_ARGS() == 0){
		user 	 = INI_STR("mtf.user");
		password = INI_STR("mtf.password");
	} else if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &user, &user_len, &password, &password_len) == FAILURE) {
		return;
	}
	
	char *result = login(url, user, password);
	char *session = login_session_id(result);
	if(session){
		zend_update_property_string(object, getThis(), "session", strlen("session"), session TSRMLS_CC);
	}
	zend_update_property_string(object, getThis(), "debug", strlen("debug"), result TSRMLS_CC);
	len = spprintf(&strg, 0, "%s", result);
	RETURN_STRINGL(strg, len, 0);
}

PHP_METHOD(MTF, real) {

	char *arg = NULL;
	int arg_len, len;
	char *strg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}
	zval *attrs, *obj;
	obj = getThis();
	attrs = zend_read_property(Z_OBJCE_P(obj), obj, "session", strlen("session"), 0 TSRMLS_CC);
	
    //php_var_dump(&attrs, 1 TSRMLS_CC);
	char *session = Z_STRVAL_P(attrs);
	
	char *xml = NULL;
	if(session){
		char *xmlpro = 	protocol_real(session, arg);
		char *url;
		asprintf(&url, "%s/add_new_member.ucs", INI_STR("mtf.url"));
		xml = conn(url, xmlpro);
		
		char *debug = NULL;
		asprintf(&debug, "%s?%s",url, xmlpro);
		zend_update_property_string(object, getThis(), "debug", strlen("debug"), debug TSRMLS_CC);
	}
	
	len = spprintf(&strg, 0, "%s", xml);
	RETURN_STRINGL(strg, len, 0);

}
PHP_METHOD(MTF, result){
	char *arg = NULL;
	int arg_len, len;
	char *strg;
	
	zend_update_property_string(object, getThis(), "debug", strlen("debug"), "" TSRMLS_CC);

	array_init(return_value);
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}
	xmlDocPtr doc = xmlParseDoc(arg);
	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return;
	}
	xmlNodePtr cur = xmlDocGetRootElement(doc);
	
	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}
	
	if (xmlStrcmp(cur->name, (const xmlChar *) "Result")) {
		fprintf(stderr,"document of the wrong type, root node != story");
		xmlFreeDoc(doc);
		return;
	}

	if ((!xmlStrcmp(cur->name, (const xmlChar *)"Result"))) {
		//printf("uri: %s\n", xmlGetProp(cur, "Code"));
		xmlAttrPtr attr;
		for(attr = cur->properties; NULL != attr; attr = attr->next){
			//printf("uri: %s\n", xmlGetProp(cur, attr->name));
			add_assoc_string(return_value, attr->name, (char *)xmlGetProp(cur, attr->name), 1);
		}
	}

	xmlFreeDoc(doc);
}

PHP_METHOD(MTF, transfer) {
	char *login = NULL;
	int login_len;
	char *amount = NULL;
	int amount_len;
	char *extdata = NULL;
	int extdata_len;
	char *dealid = NULL;
	int dealid_len;
	
	char *url, *proto;
	char *strg;
	int len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssss", &login, &login_len, &amount, &amount_len, &extdata, &extdata_len, &dealid, &dealid_len) == FAILURE) {
		return;
	}
	zval *attrs, *obj;
	obj = getThis();
	attrs = zend_read_property(Z_OBJCE_P(obj), obj, "session", strlen("session"), 0 TSRMLS_CC);
	char *session = Z_STRVAL_P(attrs);
	
	char *xml = NULL;
	char *debug = NULL;
	
	if(session){
		asprintf(&url, "%s/SpecialAPI/member_transfer.ucs",INI_STR("mtf.url"));
		asprintf(&proto, "sid=%s&Login=%s&Amount=%s&ExtData=%s&DealID=%s", session, login, amount, extdata, dealid);
		asprintf(&debug, "%s?%s",url, proto);
		
		xml = conn(url, proto);
		zend_update_property_string(object, getThis(), "debug", strlen("debug"), debug TSRMLS_CC);
		//printf("url %s\nxml: %s\n", url, xml);
	}
	
	len = spprintf(&strg, 0, "%s", xml);
	RETURN_STRINGL(strg, len, 0);
}

PHP_METHOD(MTF, balance) {
	char *login = NULL;
	int login_len;

	char *url, *proto;
	char *strg;
	int len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &login, &login_len) == FAILURE) {
		return;
	}
	zval *attrs, *obj;
	obj = getThis();
	attrs = zend_read_property(Z_OBJCE_P(obj), obj, "session", strlen("session"), 0 TSRMLS_CC);
	char *session = Z_STRVAL_P(attrs);
	
	char *xml = NULL;
	if(session){
		asprintf(&url, "%s/check_balance.ucs",INI_STR("mtf.url"));
		asprintf(&proto, "sid=%s&loginname=%s", session, login);

		xml = conn(url, proto);
		
		char *debug = NULL;
		asprintf(&debug, "%s?%s",url, proto);
		zend_update_property_string(object, getThis(), "debug", strlen("debug"), debug TSRMLS_CC);
	}
	
	len = spprintf(&strg, 0, "%s", xml);
	RETURN_STRINGL(strg, len, 0);
}

PHP_METHOD(MTF, change_password) {
	char *login = NULL;
	int login_len;

	char *password = NULL;
	int password_len;
	
	char *newpassword = NULL;
	int newpassword_len;
	
	char *url, *proto;
	char *strg;
	int len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sss", &login, &login_len, &password, &password_len, &newpassword, &newpassword_len) == FAILURE) {
		return;
	}
	zval *attrs, *obj;
	obj = getThis();
	attrs = zend_read_property(Z_OBJCE_P(obj), obj, "session", strlen("session"), 0 TSRMLS_CC);
	char *session = Z_STRVAL_P(attrs);
	
	char *xml = NULL;
	if(session){
		asprintf(&url, "%s/change_customer_pwd.ucs",INI_STR("mtf.url"));
		asprintf(&proto, "sid=%s&accountno=%s&oldpwd=%s&newpwd=%s&forgotpwd=0&platform=CASH_GT1_TR&updatedate=&", session, login, password, newpassword);

		xml = conn(url, proto);
		
		char *debug = NULL;
		asprintf(&debug, "%s?%s",url, proto);
		zend_update_property_string(object, getThis(), "debug", strlen("debug"), debug TSRMLS_CC);
	}
	
	len = spprintf(&strg, 0, "%s", xml);
	RETURN_STRINGL(strg, len, 0);
}

PHP_METHOD(MTF, change_flag) {

}

PHP_METHOD(MTF, member_info) {
}
PHP_METHOD(MTF, member_detail) {
}


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

 