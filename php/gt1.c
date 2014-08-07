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
#include "php_gt1.h"

#include "../curl.h"
#include "../protocol.h"

/* If you declare any globals in php_gt1.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(gt1)
*/

/* True global resources - no need for thread safety here */
static int le_gt1;
zend_class_entry *obj;

/* {{{ gt1_functions[]
 *
 * Every user visible function must have an entry in gt1_functions[].
 */
const zend_function_entry gt1_functions[] = {
	PHP_FE(confirm_gt1_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(hello,	NULL)
	PHP_FE(myObject,	NULL)
	PHP_FE_END	/* Must be the last line in gt1_functions[] */
};

/* }}} */

const zend_function_entry gt1_class_methods[] = {
	PHP_ME(GT1, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(GT1, demo, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GT1, login, NULL, ZEND_ACC_PUBLIC) 
	PHP_ME(GT1, real, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GT1, result, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GT1, transfer, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GT1, balance, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GT1, change_password, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

/* {{{ gt1_module_entry
 */
zend_module_entry gt1_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"gt1",
	gt1_functions,
	PHP_MINIT(gt1),
	PHP_MSHUTDOWN(gt1),
	PHP_RINIT(gt1),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(gt1),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(gt1),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_GT1_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

//#ifdef COMPILE_DL_GT1
ZEND_GET_MODULE(gt1)
//#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini */

PHP_INI_BEGIN()
    //STD_PHP_INI_ENTRY("gt1.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_gt1_globals, gt1_globals)
    //STD_PHP_INI_ENTRY("gt1.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_gt1_globals, gt1_globals)
	PHP_INI_ENTRY("test", "aaaaaaaaaaaaaaaaaaa", PHP_INI_ALL,  NULL)
	PHP_INI_ENTRY("gt1.url", "http://localhost", PHP_INI_ALL,  NULL)
	PHP_INI_ENTRY("gt1.user", "", PHP_INI_ALL,  NULL)
	PHP_INI_ENTRY("gt1.password", "", PHP_INI_ALL,  NULL)
PHP_INI_END()

/* }}} */

/* {{{ php_gt1_init_globals
 */
/* Uncomment this function if you have INI entries 
static void php_gt1_init_globals(zend_gt1_globals *gt1_globals)
{
	gt1_globals->global_value = 0;
	gt1_globals->global_string = NULL;
}
*/
/* }}} */

void init_class(TSRMLS_D) {
	zend_class_entry ce;
 
	INIT_CLASS_ENTRY(ce, "GT1", gt1_class_methods);
	//INIT_CLASS_ENTRY(ce, "GT1", Null);
	obj = zend_register_internal_class(&ce TSRMLS_CC);
 
	zend_declare_property_string(obj, "debug", strlen("debug"), "", ZEND_ACC_PUBLIC TSRMLS_CC);	
	zend_declare_property_string(obj, "session", strlen("session"), "", ZEND_ACC_PUBLIC TSRMLS_CC);	 
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(gt1)
{
	/* If you have INI entries, uncomment these lines */
	REGISTER_INI_ENTRIES();
	
	init_class(TSRMLS_C);
	
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(gt1)
{
	/* uncomment this line if you have INI entries */
	UNREGISTER_INI_ENTRIES();
	
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(gt1)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(gt1)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(gt1)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "gt1 support", "enabled");
	php_info_print_table_row(2, "gt1.author", "Neo Chan<netkiller@msn.com>");
	php_info_print_table_row(2, "gt1.url", INI_STR("gt1.url"));
	php_info_print_table_row(2, "gt1.user", INI_STR("gt1.user"));	
	php_info_print_table_row(2, "gt1.password", INI_STR("gt1.password"));	
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
/* {{{ proto string confirm_gt1_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_gt1_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "gt1", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/
PHP_FUNCTION(hello) {
    php_printf("Hello\n");
}

PHP_FUNCTION(myObject) {
    object_init(return_value);

    // add a couple of properties
    zend_update_property_string(NULL, return_value, "name", strlen("name"), "yig" TSRMLS_CC);
    zend_update_property_long(NULL, return_value, "worshippers", strlen("worshippers"), 4 TSRMLS_CC);
}

PHP_METHOD(GT1, __construct) {
	// TODO     
	//php_printf("Hello\n");  
}
PHP_METHOD(GT1, demo) {
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}
	
	char *xmlpro = 	protocol_demo(arg);
	char *url;
	asprintf(&url, "%s/add_demo_member.ucs", INI_STR("gt1.url"));		
	char *xml = conn(url, xmlpro);
	
	zend_update_property_string(obj, getThis(), "debug", strlen(xml), xml TSRMLS_CC);
	
	len = spprintf(&strg, 0, "%s", xml);
	RETURN_STRINGL(strg, len, 0);
}

PHP_METHOD(GT1, login) {
	char *url = INI_STR("gt1.url");
	char *user = NULL;
	int user_len;
	
	char *password = NULL;
	int password_len;
	
	int len;
	char *strg;
	
	if(ZEND_NUM_ARGS() == 0){
		user 	 = INI_STR("gt1.user");
		password = INI_STR("gt1.password");
	} else if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &user, &user_len, &password, &password_len) == FAILURE) {
		return;
	}
	
	char *result = login(url, user, password);
	char *session = login_session_id(result);
	if(session){
		zend_update_property_string(obj, getThis(), "session", strlen("session"), session TSRMLS_CC);
	}
	
	len = spprintf(&strg, 0, "%s", result);
	RETURN_STRINGL(strg, len, 0);
}

PHP_METHOD(GT1, real) {

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
		asprintf(&url, "%s/add_new_member.ucs", INI_STR("gt1.url"));
		xml = conn(url, xmlpro);
		//printf("xml: %s\n", xml);
		zend_update_property_string(obj, getThis(), "debug", strlen(xml), xml TSRMLS_CC);
	}
	
	len = spprintf(&strg, 0, "%s", xml);
	RETURN_STRINGL(strg, len, 0);

}
PHP_METHOD(GT1, result){
	char *arg = NULL;
	int arg_len, len;
	char *strg;
	
	//zval *arr;
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

PHP_METHOD(GT1, transfer) {
	char *login = NULL;
	int login_len;
	char *amount = NULL;
	int amount_len;
	char *extdata = NULL;
	int extdata_len;
	
	char *url, *proto;
	char *strg;
	int len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sss", &login, &login_len, &amount, &amount_len, &extdata, &extdata_len) == FAILURE) {
		return;
	}
	zval *attrs, *obj;
	obj = getThis();
	attrs = zend_read_property(Z_OBJCE_P(obj), obj, "session", strlen("session"), 0 TSRMLS_CC);
	char *session = Z_STRVAL_P(attrs);
	
	char *xml = NULL;
	if(session){
		asprintf(&url, "%s/SpecialAPI/member_transfer.ucs",INI_STR("gt1.url"));
		asprintf(&proto, "sid=%s&Login=%s&Amount=%s&ExtData=%s", session, login, amount, extdata);

		xml = conn(url, proto);
		zend_update_property_string(obj, getThis(), "debug", strlen(xml), xml TSRMLS_CC);
		//printf("url %s\nxml: %s\n", url, xml);
	}
	
	len = spprintf(&strg, 0, "%s", xml);
	RETURN_STRINGL(strg, len, 0);
}

PHP_METHOD(GT1, balance) {
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
		asprintf(&url, "%s/check_balance.ucs",INI_STR("gt1.url"));
		asprintf(&proto, "sid=%s&loginname=%s", session, login);

		xml = conn(url, proto);
		//printf("url %s\nxml: %s\n", url, xml);
		zend_update_property_string(obj, getThis(), "debug", strlen(xml), xml TSRMLS_CC);
	}
	
	len = spprintf(&strg, 0, "%s", xml);
	RETURN_STRINGL(strg, len, 0);
}

PHP_METHOD(GT1, change_password) {
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
		asprintf(&url, "%s/change_customer_pwd.ucs",INI_STR("gt1.url"));
		asprintf(&proto, "sid=%s&accountno=%s&oldpwd=%s&newpwd=%s&forgotpwd=0&platform=CASH_GT1_TR&updatedate=&", session, login, password, newpassword);

		xml = conn(url, proto);
		//printf("url %s\nxml: %s\n", url, xml);
		zend_update_property_string(obj, getThis(), "debug", strlen(xml), xml TSRMLS_CC);
	}
	
	len = spprintf(&strg, 0, "%s", xml);
	RETURN_STRINGL(strg, len, 0);
}



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

 