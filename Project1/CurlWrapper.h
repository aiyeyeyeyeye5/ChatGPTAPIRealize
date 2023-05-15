#pragma once
#include "common.h"
#include "PostData.h"
#include "curl/curl.h"
#include "NetWorkProxy.h"

class CurlWrapper
{
private:
	CURL* curl;
	struct curl_slist* headers;
	std::string postData;
	std::string OpenAIKeys = "Please write your keys there";
public:
	CurlWrapper(const std::string& data);
	~CurlWrapper();

	void setOpenAIKeys(const std::string OpenAIKeys);
	void curlRun();
};

