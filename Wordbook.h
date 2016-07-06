#pragma once

#include <map>
#include <string>

class Wordbook
{
public:
	int loadWordbook(std::string path);
	int translate(std::string path);
private:
	std::map<std::string, std::string> database;
};