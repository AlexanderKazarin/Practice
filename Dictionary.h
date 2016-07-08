#pragma once

#include <map>
#include <string>

class Dictionary
{
public:
	int loadDictionary(std::string path);
	int translate(std::string path);
	int test();
private:
	std::string dictionaryPath;
	std::map<std::string, std::string> database;
};