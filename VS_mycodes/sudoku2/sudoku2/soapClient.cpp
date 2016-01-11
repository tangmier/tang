/* soapClient.cpp
   Generated by gSOAP 2.8.20 from server.h

Copyright(C) 2000-2014, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.8.20 2014-12-07 02:33:02 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__checkRankService(struct soap *soap, const char *soap_endpoint, const char *soap_action, ns1__checkRankService *ns1__checkRankService_, ns1__checkRankServiceResponse &ns1__checkRankServiceResponse_)
{	struct __ns1__checkRankService soap_tmp___ns1__checkRankService;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:8080/wsServerExample";
	if (soap_action == NULL)
		soap_action = "http://wsServer.org/ServerB/checkRankServiceRequest";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__checkRankService.ns1__checkRankService_ = ns1__checkRankService_;
	soap_serializeheader(soap);
	soap_serialize___ns1__checkRankService(soap, &soap_tmp___ns1__checkRankService);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__checkRankService(soap, &soap_tmp___ns1__checkRankService, "-ns1:checkRankService", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__checkRankService(soap, &soap_tmp___ns1__checkRankService, "-ns1:checkRankService", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__checkRankServiceResponse_)
		return soap_closesock(soap);
	ns1__checkRankServiceResponse_.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__checkRankServiceResponse_.soap_get(soap, "ns1:checkRankServiceResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.cpp */
