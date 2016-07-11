#pragma once

#include <map>
#include <string>

class Dictionary
{
public:
	Dictionary(const char* path);
	void translateText(const char* path);
private:
	std::string pathToDictionary;
	std::map<std::string, std::string> database;
};