#include "Wordbook.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cctype>

std::vector<std::string> getText(std::string path)
{
	std::ifstream fin;
	std::vector<std::string> text;
	std::string word;
	char sym;

	fin.open(path.c_str());

	while (fin.good())
	{
		fin.get(sym);
		if (fin.eof())
			break;
		sym = tolower(sym);

		if (ispunct(sym) || isspace(sym) || iscntrl(sym))
		{
			if (word.size() > 0) text.push_back(word);
			word = sym;
			text.push_back(word);
			word.clear();
		}
		else word += sym;
	}
	if (word.size() > 0) text.push_back(word);

	return text;
}

int Wordbook::loadWordbook(std::string path)
{
	std::ifstream fin;
	std::string line;
	std::string english, russian;

	fin.open(path.c_str());

	while (std::getline(fin, line)) 
	{
		std::stringstream sin(line);
		std::getline(sin, english, ' ');
		std::getline(sin, russian, ' ');

		if (!english.empty() && !russian.empty())
			database.insert(std::pair<std::string, std::string>(english, russian));
	}

	return 0;
}

int Wordbook::translate(std::string path)
{
	std::vector<std::string> text;
	std::ofstream fout;

	fout.open("result.txt");
	text = getText(path);

	for (auto i : text)
	{
		auto word = database.find(i);
		if (word != database.end())		
			fout << word->second;
		else
			fout << i;
	}

	return 0;
}