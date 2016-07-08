#include "Dictionary.h"
#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>

int toLowRegister(std::string& word)
{
	for (int i = 0; i < word.size(); i++)
		word[i] = tolower(word[i]);

	return 0;
}

std::vector<std::string> getText(std::string path)
{
	std::ifstream fin;
	std::vector<std::string> text;
	std::string word;
	char sym;

	fin.open(path.c_str());
	if (!fin.is_open())
		throw std::runtime_error("Ошибка: файл с текстом не открылся.");

	while (fin.good())
	{
		fin.get(sym);
		if (fin.eof())
			break;

		if ((isspace(sym) || iscntrl(sym)) && !word.empty())
		{
			toLowRegister(word);
			text.push_back(word);
			word.clear();
		}
		else if (isalpha(sym))
			word += sym;
	}
	if (word.size())
	{
		toLowRegister(word);
		text.push_back(word);
	}

	fin.close();
	return text;
}

int Dictionary::loadDictionary(std::string path)
{
	std::ifstream fin;
	std::string line;
	std::string english, russian;

	fin.open(path.c_str());
	if (!fin.is_open())
		throw std::runtime_error("Ошибка: файл со словарем не открылся.");
	dictionaryPath = path;

	while (std::getline(fin, line)) 
	{
		std::stringstream sin(line);
		std::getline(sin, english, ' ');
		std::getline(sin, russian, ' ');

		if (!english.empty() && !russian.empty())
		{
			toLowRegister(english);
			toLowRegister(russian);
			database.insert(std::pair<std::string, std::string>(english, russian));
		}
	}

	fin.close();
	return 0;
}

int Dictionary::translate(std::string path)
{
	std::vector<std::string> text;
	std::string buffer;
	std::ofstream fout;
	std::ofstream fout_d;
	char command;

	text = getText(path);
	fout.open("result.txt");
	if (!fout.is_open())
		throw std::runtime_error("Ошибка: файл с результатом не создался.");
	fout_d.open(dictionaryPath.c_str(), std::ios_base::app);
	if (!fout_d.is_open())
		throw std::runtime_error("Ошибка: файл со словарем не открылся.");

	for (auto i : text)
	{
		auto word = database.find(i);
		if (word != database.end())
			fout << word->first << " - " << word->second << std::endl; 
		else
		{
			std::cout << i << " - неизвестное слово" << std::endl;
			std::cout << "Хотите ли Вы дополнить словарь? ('y' (англ) если 'да')" << std::endl;
			std::cin >> command;
			switch (command)
			{
				case 'y':
					std::cout << "Введите перевод слова " << i <<  std::endl;
					std::cin >> buffer;
					toLowRegister(buffer);
					if (!buffer.empty())
					{
						database.insert(std::pair<std::string, std::string>(i, buffer));
						fout_d << std::endl << i << " " << buffer;
						fout << i << " - " << buffer << std::endl;
					}
					break;
				default:
					break;
			}
		}
	}

	fout.close();
	fout_d.close();
	return 0;
}

int Dictionary::test()
{
	srand(time(NULL));
	int pos;
	std::string buffer;

	pos = rand() % (database.size() - 1);
	auto element = database.begin();
	for (int i = 0; i < pos; i++)
		element++;

	std::cout << "Введите перевод слова " << element->first << std::endl;
	std::cin >> buffer;
        toLowRegister(buffer);
	if (element->second == buffer)
		std::cout << "Верно!" << std::endl;
	else
		std::cout << "Неверно. Правильный перевод - " << element->second << std::endl;

	return 0;
}