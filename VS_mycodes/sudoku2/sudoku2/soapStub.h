/* soapStub.h
   Generated by gSOAP 2.8.20 from server.h

Copyright(C) 2000-2014, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapStub_H
#define soapStub_H
#define SOAP_NAMESPACE_OF_ns1	"http://wsServer.org/"
#include "stdsoap2.h"
#if GSOAP_VERSION != 20820
# error "GSOAP VERSION 20820 MISMATCH IN GENERATED CODE VERSUS LIBRARY CODE: PLEASE REINSTALL PACKAGE"
#endif


/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes and Structs                                                        *
 *                                                                            *
\******************************************************************************/


#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_ns1__checkRankService
#define SOAP_TYPE_ns1__checkRankService (7)
/* ns1:checkRankService */
class SOAP_CMAC ns1__checkRankService
{
public:
	char *arg0;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 7; } /* = unique type id SOAP_TYPE_ns1__checkRankService */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__checkRankService() { ns1__checkRankService::soap_default(NULL); }
	virtual ~ns1__checkRankService() { }
};
#endif

#ifndef SOAP_TYPE_ns1__checkRankServiceResponse
#define SOAP_TYPE_ns1__checkRankServiceResponse (8)
/* ns1:checkRankServiceResponse */
class SOAP_CMAC ns1__checkRankServiceResponse
{
public:
	int __sizereturn_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* sequence of elements <return> */
	char **return_;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 8; } /* = unique type id SOAP_TYPE_ns1__checkRankServiceResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__checkRankServiceResponse() { ns1__checkRankServiceResponse::soap_default(NULL); }
	virtual ~ns1__checkRankServiceResponse() { }
};
#endif

#ifndef SOAP_TYPE___ns1__checkRankService
#define SOAP_TYPE___ns1__checkRankService (14)
/* Operation wrapper: */
struct __ns1__checkRankService
{
public:
	ns1__checkRankService *ns1__checkRankService_;	/* optional element of type ns1:checkRankService */
public:
	int soap_type() const { return 14; } /* = unique type id SOAP_TYPE___ns1__checkRankService */
};
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (15)
/* SOAP Header: */
struct SOAP_ENV__Header
{
public:
	int soap_type() const { return 15; } /* = unique type id SOAP_TYPE_SOAP_ENV__Header */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (16)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
public:
	int soap_type() const { return 16; } /* = unique type id SOAP_TYPE_SOAP_ENV__Code */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (18)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	char *__any;
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
public:
	int soap_type() const { return 18; } /* = unique type id SOAP_TYPE_SOAP_ENV__Detail */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (21)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
public:
	int soap_type() const { return 21; } /* = unique type id SOAP_TYPE_SOAP_ENV__Reason */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (22)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
public:
	char *faultcode;	/* optional element of type xsd:QName */
	char *faultstring;	/* optional element of type xsd:string */
	char *faultactor;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of type SOAP-ENV:Detail */
public:
	int soap_type() const { return 22; } /* = unique type id SOAP_TYPE_SOAP_ENV__Fault */
};
#endif

#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif


/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Server-Side Operations                                                     *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 __ns1__checkRankService(struct soap*, ns1__checkRankService *ns1__checkRankService_, ns1__checkRankServiceResponse &ns1__checkRankServiceResponse_);

/******************************************************************************\
 *                                                                            *
 * Server-Side Skeletons to Invoke Service Operations                         *
 *                                                                            *
\******************************************************************************/

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___ns1__checkRankService(struct soap*);

/******************************************************************************\
 *                                                                            *
 * Client-Side Call Stubs                                                     *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__checkRankService(struct soap *soap, const char *soap_endpoint, const char *soap_action, ns1__checkRankService *ns1__checkRankService_, ns1__checkRankServiceResponse &ns1__checkRankServiceResponse_);

#endif

/* End of soapStub.h */