#ifndef CRYPTOPP_BASE64_H
#define CRYPTOPP_BASE64_H

#include "basecode.h"

NAMESPACE_BEGIN(CryptoPP)

#pragma warning(disable: 4511 4512)

//! Base64 Encoder Class 
class Base64Encoder : public SimpleProxyFilter
{
public:
	Base64Encoder(BufferedTransformation *attachment = NULL, bool insertLineBreaks = true, int maxLineLength = 72)
		: SimpleProxyFilter(new BaseN_Encoder(new Grouper), attachment)
	{
		IsolatedInitialize(MakeParameters("InsertLineBreaks", insertLineBreaks)("MaxLineLength", maxLineLength));
	}

	void IsolatedInitialize(const NameValuePairs &parameters);
};

//! Base64 Decoder Class 
class Base64Decoder : public BaseN_Decoder
{
public:
	Base64Decoder(BufferedTransformation *attachment = NULL)
		: BaseN_Decoder(GetDecodingLookupArray(), 6, attachment) {}

	void IsolatedInitialize(const NameValuePairs & /*parameters*/) {}

private:
	static const int *GetDecodingLookupArray();
};

#pragma warning(default: 4511 4512)

NAMESPACE_END

#endif