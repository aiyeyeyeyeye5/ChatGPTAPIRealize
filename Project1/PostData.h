#pragma once
#include "common.h"
#include "nlohmann/json.hpp"
typedef nlohmann::json JSON;

class PostData
{
private:
	JSON json;
	std::string model = "gpt - 3.5 - turbo - 0301";
	double temperature = 0.8;
public:
	PostData(const std::string& data);
	~PostData();

	std::string getModel();
	void setModel(const std::string model);

	double getTemperature();
	void setTemperature(const double temperature);
};

