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

char * login(char * user, char * pass){
	char * proto;
	char * result;
	
	asprintf(&proto, "loginname=%s&pwd=%s&type=OP",user, pass);
	result = conn("http://59.152.226.199:3355/login.ucs", proto);
	
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

	
	//while (cur != NULL) {
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

char * protocol_real(char * chinese_name){
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
