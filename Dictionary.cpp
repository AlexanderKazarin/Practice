#include "Dictionary.h"
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <cctype>

void toLowerCase(std::string& line)
{
	for (auto it = line.begin(); it != line.end(); it++)
		*it = tolower(*it);
}

std::vector<std::string> getText(const char* path)
{
	std::vector<std::string> text;
	std::ifstream textStream;
	std::string line;
	std::string buf;
	std::regex exp("[[:punct:]]", std::regex::extended); 

	textStream.open(path);
	if (!textStream.is_open())
		throw std::string("Файл не найден!");	 

	while (std::getline(textStream, line))
	{
		toLowerCase(line);
		line = std::regex_replace(line, exp, "");
		std::stringstream lineStream(line);

		while (std::getline(lineStream, buf, ' '))
			text.push_back(buf);
	}

	return text;
}

Dictionary::Dictionary(const char* path)
{
	std::ifstream dictionaryStream;
	std::string line;
	std::string english, russian;

	pathToDictionary = static_cast<std::string>(path);
	dictionaryStream.open(path);
	if (!dictionaryStream.is_open())
		throw std::string("Файл не найден!");

	while (std::getline(dictionaryStream, line)) 
	{
		toLowerCase(line);
		std::stringstream lineStream(line);
		std::getline(lineStream, english, ' ');
		std::getline(lineStream, russian, ' ');

		if (!english.empty() && !russian.empty())
			database.insert(std::pair<std::string, std::string>(english, russian));
	}
}

void Dictionary::translateText(const char* path)
{
	std::ofstream resultStream;
	std::ofstream dictionaryStream;
	auto text = getText(path);
	std::string buf;
	char command;

	resultStream.open("result.txt");
	dictionaryStream.open(pathToDictionary.c_str(), std::ios_base::app);
	if (!resultStream.is_open() || !dictionaryStream.is_open())
		throw std::string("Файл не найден!");

	for (auto word : text)
	{
		auto data = database.find(word);
		if (data != database.end())
			resultStream << word << " - " << data->second << '\n';
		else
		{
			std::cout << "Хотите ли Вы дополнить словарь? (y (англ) если 'да')\n";
			std::cin >> command;
			if (command == 'y')
			{
				std::cout << "Введите перевод слова " << word << '\n';
				std::cin >> buf;
				toLowerCase(buf);
				database.insert(std::pair<std::string, std::string>(word, buf));
				dictionaryStream << word << " " << buf << '\n';
				resultStream << word << " - " << buf << '\n';				
			}
		}	
	}
}