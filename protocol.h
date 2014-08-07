#include <libxml/parser.h>
#include <libxml/tree.h>

char * protocol_demo(char * chinese_name){
	char * rev;
	xmlDocPtr doc = NULL;
	xmlNodePtr data = NULL, amsinfo = NULL, cus = NULL, cusinfo = NULL;

	doc = xmlNewDoc(BAD_CAST "1.0"); // create a new xml document.
	data = xmlNewNode(NULL, BAD_CAST "Data"); // create a root node.
	xmlNewProp(data, BAD_CAST "SessionId", BAD_CAST "Ams3ToAms2ApplyTrDemoMember");
	xmlDocSetRootElement(doc, data);

	amsinfo = xmlNewChild(data, NULL, BAD_CAST "AMSInfo", NULL);
	xmlNewProp(amsinfo, BAD_CAST "ParentName", BAD_CAST "c1");
	xmlNewProp(amsinfo, BAD_CAST "NickName", BAD_CAST "w112");
	xmlNewProp(amsinfo, BAD_CAST "pwd", BAD_CAST "1234qwer");
	xmlNewProp(amsinfo, BAD_CAST "Limit", BAD_CAST "0");
	xmlNewProp(amsinfo, BAD_CAST "Platform", BAD_CAST "CASH_GT1_TR");
	xmlNewProp(amsinfo, BAD_CAST "Demo", BAD_CAST "1");
	xmlNewProp(amsinfo, BAD_CAST "ExpireTime", BAD_CAST "2014-07-23");
	xmlNewProp(amsinfo, BAD_CAST "Operator", BAD_CAST "test1");
	xmlNewProp(amsinfo, BAD_CAST "FixLeverage", BAD_CAST "0");

	cus = xmlNewChild(data, NULL, BAD_CAST "Cus", NULL);
	xmlNewProp(cus, BAD_CAST "CREATE_USER", BAD_CAST "test1");
	xmlNewProp(cus, BAD_CAST "CREATE_IP", BAD_CAST "175.45.18.98");
	xmlNewProp(cus, BAD_CAST "CREATE_DATE", BAD_CAST "2014-04-01 13:37:23");

	cusinfo = xmlNewChild(data, NULL, BAD_CAST "CusInfo", NULL);
	xmlNewProp(cusinfo, BAD_CAST "CHINESE_NAME", BAD_CAST chinese_name);
	xmlNewProp(cusinfo, BAD_CAST "MOBILE_PHONE", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "EMAIL", BAD_CAST "");
	
	xmlAddChild(data, amsinfo);
	xmlAddChild(data, cus);
	
	xmlChar *s;
	int size;
	xmlDocDumpMemory(doc, &s, &size);
	asprintf(&rev, "%s", (char *)s+22);
	xmlFree(s);
	
	//xmlSaveFormatFileEnc("-", doc, "UTF-8", 0);

	xmlFreeDoc(doc);
	xmlCleanupParser();

	return(rev);
}

char * login(char * host, char * user, char * password){
	char * url;
	char * proto;
	char * result;
	
	asprintf(&url, "%s/login.ucs", host);
	asprintf(&proto, "loginname=%s&pwd=%s&type=OP", user, password);
	result = conn(url, proto);
	
	return result;
}

char * login_session_id(char * result){
	char * sessionid = "";
	xmlDocPtr doc = xmlParseDoc(result);
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
		xmlChar *code;
		code = xmlGetProp(cur, "Code");
		
		if(!xmlStrcmp(code, (const xmlChar *)"AMS_OK")){
			//printf("code: |%s|%s|\n", code, (const xmlChar *)"AMS_OK");
			xmlChar *session;
			xmlNodePtr node = cur->xmlChildrenNode;

			while (node != NULL) {
				if (!(xmlStrcmp(node->name, (const xmlChar *)"SessionId"))) {
					session = xmlNodeGetContent(node);
					asprintf(&sessionid, "%s", (char *)session);
					//printf("sess: %s\n", session);	
					break;
				}
				cur = cur->next;
			}
			xmlFree(session);
		}		
		xmlFree(code);
	}
	xmlFreeDoc(doc);
	xmlCleanupParser();
	return sessionid;
}

char * protocol_real(char * sessionid, char * chinese_name){
	char * rev;
	xmlDocPtr doc = NULL;
	xmlNodePtr data = NULL, amsinfo = NULL, market = NULL, product = NULL, cus = NULL, cusinfo = NULL;

	doc = xmlNewDoc(BAD_CAST "1.0"); // create a new xml document.
	data = xmlNewNode(NULL, BAD_CAST "Data"); // create a root node.
	xmlNewProp(data, BAD_CAST "SessionId", BAD_CAST sessionid);
	xmlDocSetRootElement(doc, data);

	amsinfo = xmlNewChild(data, NULL, BAD_CAST "AMSInfo", NULL);
	xmlNewProp(amsinfo, BAD_CAST "ParentName", BAD_CAST "F0000376");
	xmlNewProp(amsinfo, BAD_CAST "LoginName", BAD_CAST "");
	xmlNewProp(amsinfo, BAD_CAST "pwd", BAD_CAST "");
	xmlNewProp(amsinfo, BAD_CAST "NickName", BAD_CAST "");
	xmlNewProp(amsinfo, BAD_CAST "Limit", BAD_CAST "0");
	xmlNewProp(amsinfo, BAD_CAST "Platform", BAD_CAST "CASH_GT1_TR");
	xmlNewProp(amsinfo, BAD_CAST "Demo", BAD_CAST "0");
	
	market = xmlNewChild(amsinfo, NULL, BAD_CAST "Market", NULL);
	xmlNewProp(market, BAD_CAST "Code", BAD_CAST "c396_TR01");
	
	product = xmlNewChild(market, NULL, BAD_CAST "Product", NULL);
	xmlNewProp(product, BAD_CAST "Code", BAD_CAST "GT1/PM/LLG");
	xmlNewProp(product, BAD_CAST "SpreadShare", BAD_CAST "0");
	xmlNewProp(product, BAD_CAST "HandleFee", BAD_CAST "0");


	cus = xmlNewChild(data, NULL, BAD_CAST "Cus", NULL);
	xmlNewProp(cus, BAD_CAST "FLAG", BAD_CAST "0");
	xmlNewProp(cus, BAD_CAST "REALNAME", BAD_CAST "555");
	xmlNewProp(cus, BAD_CAST "ACTIVE", BAD_CAST "0");
	xmlNewProp(cus, BAD_CAST "CREATE_USER", BAD_CAST "test1");
	xmlNewProp(cus, BAD_CAST "CREATE_IP", BAD_CAST "175.45.18.98");
	xmlNewProp(cus, BAD_CAST "CREATE_DATE", BAD_CAST "2014-04-01 13:37:23");
	xmlNewProp(cus, BAD_CAST "CLIENT_CLASS", BAD_CAST "0");
			
	cusinfo = xmlNewChild(data, NULL, BAD_CAST "CusInfo", NULL);
	xmlNewProp(cusinfo, BAD_CAST "TITLE", BAD_CAST "Mr");
	xmlNewProp(cusinfo, BAD_CAST "CHINESE_NAME", BAD_CAST chinese_name);
	xmlNewProp(cusinfo, BAD_CAST "ENGLISH_NAME", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "ACCOUNT_STATUS", BAD_CAST "A");
	xmlNewProp(cusinfo, BAD_CAST "ID_DOCUMENT", BAD_CAST "1");
	xmlNewProp(cusinfo, BAD_CAST "ID_DOCUMENT_NUMBER", BAD_CAST "555");
	xmlNewProp(cusinfo, BAD_CAST "ID_DOCUMENT_COUNTRY", BAD_CAST "China");
	xmlNewProp(cusinfo, BAD_CAST "DATE_OF_BIRTH", BAD_CAST "1921-1-1");
	xmlNewProp(cusinfo, BAD_CAST "NATIONALITY", BAD_CAST "China");
	xmlNewProp(cusinfo, BAD_CAST "HOME_PHONE", BAD_CAST "86-555");
	xmlNewProp(cusinfo, BAD_CAST "MOBILE_PHONE", BAD_CAST "86-555");
	xmlNewProp(cusinfo, BAD_CAST "ADDRESS0", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "ADDRESS1", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "ADDRESS2", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "PROVINCE", BAD_CAST "anhui");
	xmlNewProp(cusinfo, BAD_CAST "COUNTRY", BAD_CAST "China");
	xmlNewProp(cusinfo, BAD_CAST "POSTAL_CODE", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "EMAIL", BAD_CAST "");
	
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_TITLE", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_CHINESE_NAME", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_ENGLISH_NAME", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_DOCUMENT", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_ID_DOCUMENT_NUMBER", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_ID_DOCUMENT_COUNTRY", BAD_CAST "China");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_DATE_OF_BIRTH", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_NATIONALITY", BAD_CAST "China");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_HOME_PHONE", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_MOBILE_PHONE", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_ADDRESS0", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_ADDRESS1", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_ADDRESS2", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_PROVINCE", BAD_CAST "anhui");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_COUNTRY", BAD_CAST "China");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_POSTAL_CODE", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "CONTACT_EMAIL", BAD_CAST "");
	
	xmlNewProp(cusinfo, BAD_CAST "EQUITY_TYPE", BAD_CAST "Holder");
	xmlNewProp(cusinfo, BAD_CAST "EQUITY_CHINESE_NAME", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "EQUITY_ENGLISH_NAME", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "EQUITY_DOCUMENT", BAD_CAST "IdCard");
	xmlNewProp(cusinfo, BAD_CAST "EQUITY_DOCUMENT_NUMBER", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "EQUITY_ADDRESS0", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "EQUITY_ADDRESS1", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "EQUITY_ADDRESS2", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "EQUITY_PROVINCE", BAD_CAST "anhui");
	xmlNewProp(cusinfo, BAD_CAST "EQUITY_COUNTRY", BAD_CAST "China");
	
	xmlNewProp(cusinfo, BAD_CAST "PRINCIPALFINAL", BAD_CAST "Holder");
	
	xmlNewProp(cusinfo, BAD_CAST "PRINCIPAL_CHINESE_NAME", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "PRINCIPAL_ENGLISH_NAME", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "PRINCIPAL_DOCUMENT", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "PRINCIPAL_ID_DOCUMENT_NUMBER", BAD_CAST "");
	xmlNewProp(cusinfo, BAD_CAST "PRINCIPAL_ADDRESS0", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "PRINCIPAL_ADDRESS1", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "PRINCIPAL_ADDRESS2", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "PRINCIPAL_PROVINCE", BAD_CAST "anhui");	
	xmlNewProp(cusinfo, BAD_CAST "PRINCIPAL_COUNTRY", BAD_CAST "China");	
	
	xmlNewProp(cusinfo, BAD_CAST "BANK", BAD_CAST "SCB");	
	xmlNewProp(cusinfo, BAD_CAST "BANK_ACCOUNT_NAME", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "BANK_ACCOUNT_NUMBER", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "INTERNATIONAL_REMITTANCE_CODE", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "BANK_ADDRESS_0", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "BANK_ADDRESS_1", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "BANK_ADDRESS_2", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "BANK_COUNTRY", BAD_CAST "China");	
	xmlNewProp(cusinfo, BAD_CAST "CURRENCY", BAD_CAST "USD");	
	xmlNewProp(cusinfo, BAD_CAST "CREATE_USER", BAD_CAST "dong4");	
	xmlNewProp(cusinfo, BAD_CAST "CREATE_IP", BAD_CAST "175.45.18.98");	
	xmlNewProp(cusinfo, BAD_CAST "CREATE_DATE", BAD_CAST "2014-04-28 13:34:35");	
	xmlNewProp(cusinfo, BAD_CAST "PLATFORM", BAD_CAST "CASH_GT1_TR");	
	
	xmlNewProp(cusinfo, BAD_CAST "EMPLOYMENT", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "EMPLOYER", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "RELATIONSHIP", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "RELATION", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "OBJECTIVE", BAD_CAST "");	
	xmlNewProp(cusinfo, BAD_CAST "EXPERIENCE", BAD_CAST "");
	
	//xmlAddChild(data, amsinfo);
	//xmlAddChild(data, cus);
	
	xmlChar *s;
	int size;
	xmlDocDumpMemory(doc, &s, &size);
	asprintf(&rev, "%s", (char *)s+22);
	xmlFree(s);
	
	//xmlSaveFormatFileEnc("-", doc, "UTF-8", 0);

	xmlFreeDoc(doc);
	xmlCleanupParser();

	return(rev);
}
