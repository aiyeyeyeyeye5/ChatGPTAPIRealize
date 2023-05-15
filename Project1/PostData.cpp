#include "PostData.h"

PostData::PostData(const std::string& data) {
	json["model"] = model;
	json["message"] = { { {"role", "user"}, {"content", data} } };
	json["temperature"] = temperature;
	std::cout << "data load finished" << std::endl;
}

PostData::~PostData() {
	std::cout << "data freed" << std::endl;
}

std::string PostData::getModel()
{
	return model;
}

void PostData::setModel(const std::string model) : model(model)
{
	std::cout << "model load finished" << std::endl;
}

double PostData::getTemperature()
{
	return temperature;
}

void PostData::setTemperature(const double temperature) : temperature(temperature)
{
	std::cout << "temperature load finished" << std::endl;
}
